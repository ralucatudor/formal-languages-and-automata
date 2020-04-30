#include "DFA.hpp"

#include <queue>

const std::string DFA::SIGMA = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

DFA::DFA() {}

DFA::DFA(std::vector <std::map <char, int>> transitions, int start_state, std::set <int> final_states): 
    transitions(transitions), start_state(start_state), final_states(final_states)
{}

std::ostream& operator << (std::ostream& out, const DFA& automaton)
{
    out << "Number of states = " << (int)automaton.transitions.size() - 1 << "\n";
    for (int state = 1; state < (int)automaton.transitions.size(); ++state) {
        for (auto& map : automaton.transitions[state]) {
            if (map.second) {
                out << state << " --" << map.first << "--> " << map.second << '\n';
            }       
        }
    }
    out << "Initial state = " << automaton.start_state << '\n';

    out << "Final state(s): ";
    for (auto& state : automaton.final_states) {
        out << state << ' ';
    }
    out << '\n';

    return out;
}

void DFA::markUnreachableStates() 
{
    // Unreachable states are not reachable from the initial state of the DFA, for any input string.
    isUnreachableState = std::vector<bool>((int)transitions.size(), true); 
    std::queue<int> q;
    q.push(start_state);
    isUnreachableState[start_state] = false;
    while (!q.empty()) {
        int state = q.front();
        q.pop();
        for (auto& newTransition : transitions[state]) {
            if (isUnreachableState[newTransition.second]) {
                isUnreachableState[newTransition.second] = false; 
                q.push(newTransition.second);   // push new state
            }
        }
    }
}

void DFA::markDeadStates()
{
    int nr_states = (int)transitions.size();
    std::vector<std::vector<int>> reverseTransitions(nr_states);

    for (int state = 1; state < nr_states; ++state){
        for (auto map : transitions[state]){
            reverseTransitions[map.second].emplace_back(state);
        }
    }

    // isDeadState[q] = 1 if I cannot reach a final state from q
    isDeadState = std::vector<bool>(nr_states, true); 
    std::queue<int> q;
    for (auto& state : final_states) {  // starting from the final states set
        q.push(state);
        isDeadState[state] = false;
    }
    while (!q.empty()) {
        int state = q.front();
        q.pop();
        for (auto& new_state : reverseTransitions[state]) { // then going to every state that can be reached
            if (isDeadState[new_state] == true) {
                isDeadState[new_state] = false;
                q.push(new_state);
            }
        }
    }
}

bool DFA::isReachableState(int state) const
{
    return (isDeadState[state] == false && isUnreachableState[state] == false);
}

// DFA Minimization using Myhill-Nerode Theorem
DFA DFA::minimize()
{
    markUnreachableStates();
    markDeadStates();

    // Step 1. Find equivalent states
    int nr_states = (int)transitions.size();

    std::vector <std::vector <bool>> areEquivalent(nr_states, std::vector <bool>(nr_states, true));

	for (int q = 1; q < nr_states; ++q) {
		for (int r = q + 1; r < nr_states; ++r) {
			bool qIsFinalState = final_states.find(q) != final_states.end();
			bool rIsFinalState = final_states.find(r) != final_states.end();
			if (qIsFinalState != rIsFinalState) {
				areEquivalent[q][r] = false;
            }
        }
	}

    // for each pair of states (q, r)
    // if states (delta(q, input_symbol), delta(r, input_symbol)) are not equivalent
    // then (q, r) are also not equivalent
    bool hasUnseenChanges = 1;
    while (hasUnseenChanges) {
        hasUnseenChanges = 0;
        for (int q = 1; q < nr_states; ++q) {
		    for (int r = q + 1; r < nr_states; ++r) {
                for (char input_symbol : SIGMA) {
                    if (transitions[q][input_symbol] && transitions[r][input_symbol]) {
                        int qNext = transitions[q][input_symbol];
                        int rNext = transitions[r][input_symbol];
                        if (!areEquivalent[qNext][rNext] && areEquivalent[q][r]) {
                            areEquivalent[q][r] = false;
                            hasUnseenChanges = 1;
                        }
                    }
                }
            }
        }
    }
  
    std::vector <std::set<int>> groups;
    std::vector <bool> seen(nr_states, false);
    for (int state = 1; state < nr_states; ++state) {
        if (!seen[state]) {
            seen[state] = true;
            groups.push_back({state});
            int current_pos = groups.size() - 1;    // current group position

            std::queue <int> q; // queue for finding out the whole group of eqv. states with 'state'
            q.push(state);      // first I have just state
            while (!q.empty()) {
                int q1 = q.front();
                q.pop();
                // iterate through all the eqv. states with q1
                for (int q2 = q1 + 1; q2 < nr_states; ++q2) {
                    if (areEquivalent[q1][q2]) {
                        if (!seen[q2]) {
                            seen[q2] = true;
                            q.push(q2);
                            groups[current_pos].insert(q2);
                        }
                    }
                }

            }
        }
    }

    // for (auto& new_state : groups) {
    //     for (auto& elem : new_state) {
    //         std::cout << elem << ' ';
    //     }
    //     std::cout << '\n';
    // }

    std::vector <int> state_index(nr_states);

    for (size_t index = 0; index < (int)groups.size(); ++index) {
        for (auto& state : groups[index]) {
            state_index[state] = index + 1;
        }
    }

    // for (int state = 1; state < nr_states; ++state)
    //     std::cout << state_index[state] << ' ';

    int new_nr_states = (int)groups.size() + 1;

    int new_start_state = state_index[start_state];
    std::set<int> new_final_states;
    std::vector<std::map<char, int>> new_transitions(new_nr_states);

    for (int new_state = 1; new_state < new_nr_states; ++new_state) {
        int state = *groups[new_state - 1].begin();     // I choose the first state of the current group
        // all states in the group are equivalent, so I may choose any state
        if (final_states.find(state) != final_states.end()) {
            new_final_states.insert(new_state);
        }

        for (auto map : transitions[state]) {
            if (map.second) {
                if (isReachableState(map.second)) {
                    new_transitions[new_state][map.first] = state_index[map.second];
                }
            }
        }
    }

    return DFA(new_transitions, new_start_state, new_final_states);
}