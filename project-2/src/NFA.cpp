#include "NFA.hpp"

#include <queue>

const std::string NFA::SIGMA = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

char NFA::lambda = '$';

NFA::NFA() {}

NFA::NFA(int nr_states):
    transitions(std::vector<std::map<char, std::set<int>>>(nr_states + 1)) 
    // +1 because I consider the first state to be 1, not zero
{}
    
std::istream& operator >> (std::istream& in, NFA& automaton)
{
    int n, m;
    in >> n;    // n = number of states
    in >> m;    // m = number of transition functions

    automaton = NFA(n);   // calling the constructor

    for (int i = 0; i < m; ++i) {
        int q1, q2; // states corresponding to a transition function
        char ch;    // character of the input alphabet
        in >> q1 >> q2 >> ch;

        if (ch == automaton.lambda && q1 == q2) {
            continue;
        }

        automaton.transitions[q1][ch].insert(q2);
    }

    in >> automaton.start_state; // start state, q0

    int t;
    in >> t; // cardinal of the final state set, F

    for (int i = 0; i < t; ++i) {
        int q;
        in >> q;
        automaton.final_states.insert(q);   // store the final state set in unordered_set
    }

    return in;
}

std::ostream& operator << (std::ostream& out, const NFA& automaton)
{
    out << "Number of states = " << (int)automaton.transitions.size() - 1 << "\n";
    for (int state = 1; state < (int)automaton.transitions.size(); ++state) {
        for (auto& map : automaton.transitions[state]) {
            for (auto& next_state : map.second) {
                out << state << " --" << map.first << "--> " << next_state << '\n';
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

void NFA::convert_lambda_NFA_to_NFA()
{
    int nr_states = transitions.size();

    bool hasUnseenChanges = 1;
    while (hasUnseenChanges) {
        hasUnseenChanges = 0;

        // lambda-Completion &  lambda-Transition Removal
        // For all p, q, r in Q:
        // whenever (p, lambda, q), (q, a, r) are in delta, add (p, a, r) to delta 
        // until no new transitions are added to delta and let this be delta'.

        for (int p = 1; p < nr_states; p++) {   // for all p
            if (!transitions[p].count(lambda))
                continue;

            for (int q : transitions[p][lambda]) {  // for all q, with (p, lambda, q) in delta
                for (auto& map : transitions[q]) {  // iterate through all transitions from q
                    for (auto& r : map.second) {
                        transitions[p][map.first].insert(r);    // add (p, a, r) to delta 
                        hasUnseenChanges = 1;
                    }
                }

                // if q is final state and p is not
                if (final_states.find(q) != final_states.end() && final_states.find(p) == final_states.end()) {
                    final_states.insert(p);     // p final state
                    hasUnseenChanges = 1;
                }
            }
            transitions[p][lambda].clear();     // delete lambda-transitions
        }
    }
}

// Transformation of an NFA to a DFA
NFA::operator DFA()
{
    std::vector <std::map <char, int>> new_transitions;
    new_transitions.emplace_back(); // because the state count starts at 1, therefore pos zero is not used :(

    int new_start_state = start_state;
    std::set <int> new_final_states; 

    std::map <std::set <int>, int> state_subset_index;
    std::set <int> aux; // current new state (in DFA) created from a state subset (in NFA)

    std::queue<std::set<int>> queue;

    int current_index = 1;
    aux.insert(start_state);
    queue.push(aux);
    if (final_states.find(start_state) != final_states.end())    // it is final state
        new_final_states.insert(current_index);
    state_subset_index[aux] = current_index++;
    new_transitions.emplace_back(std::map<char, int>());
    aux.clear();

    while (!queue.empty()) {
        std::set<int> current_states = queue.front();
        queue.pop();

        for (char input_symbol : SIGMA) {
            for (auto& p : current_states) {
                for (auto& q: transitions[p][input_symbol]) {
                    aux.insert(q);
                }
            }

            if (aux.empty())
                continue;
         
            if (state_subset_index.find(aux) == state_subset_index.end()) {
                state_subset_index[aux] = current_index++;
                for (auto& q : aux) {
                    if (final_states.find(q) != final_states.end())    // is final state
                        new_final_states.insert(state_subset_index[aux]);
                }
                
                new_transitions.emplace_back(std::map<char, int>());
                queue.push(aux);
            }  
            new_transitions[state_subset_index[current_states]][input_symbol] = state_subset_index[aux];
            aux.clear();
        }
    }

    return DFA(new_transitions, new_start_state, new_final_states);
}
