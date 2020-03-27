#include "automaton.hpp"

Automaton::Automaton() {}

Automaton::Automaton(int nr_states):
    transitions(std::vector<std::unordered_map<char, std::vector<int>>>(nr_states + 1)),
    reverseTransitions(std::vector<std::vector<int>>(nr_states + 1)) {}

std::istream& operator >> (std::istream& in, Automaton& automaton)
{
    int n, m;
    in >> n;    // n = number of states
    in >> m;    // m = number of transition functions

    automaton = Automaton(n);   // calling the constructor

    for (int i = 0; i < m; i++) {
        int q1, q2; // states corresponding to a transition function
        char ch;    // character of the input alphabet
        in >> q1 >> q2 >> ch;
        automaton.transitions[q1][ch].emplace_back(q2);
        automaton.reverseTransitions[q2].emplace_back(q1);
    }

    in >> automaton.start_state; // start state

    int t;
    in >> t; // cardinal of the final state set

    for (int i = 0; i < t; i++) {
        int q;
        in >> q;
        automaton.final_states.insert(q);   // store the final state set in unordered_set
    }

    automaton.markDeadStates();

    return in;
}

void Automaton::markDeadStates()
{
    isDeadState = std::vector<bool>(transitions.size() + 1, true);
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

bool Automaton::isAccepted(std::string word)
{
    std::vector<bool> inQueue(transitions.size() + 1, 0);
    std::vector<int> q;
    q.emplace_back(start_state);

    for(int i = 0; i < (int)word.size(); i++) {
        char letter = word[i];
        std::vector<int> temp;   // next states

        for (auto& node : q) {  // current states
            for (auto& son : transitions[node][letter]) {
                if (!inQueue[son] && !isDeadState[son]) {   // checking if inQueue[son] = 1 is necessary so that
                                                            // I will not "revisit" a state which I have seen before
                                                            // with the same (sub-word) length
                    temp.emplace_back(son);
                    inQueue[son] = 1;
                }
            }
        }
        // clearing the queue
        for(auto& node : temp)
            inQueue[node] = 0;

        q = temp;   // the next states will become current states
    }

    for(auto& node : q)
        if (final_states.find(node) != final_states.end())
            return true;
    return false;
}


std::vector<std::string> Automaton::smallestAcceptedWords(int total_words) const
{
    struct queueElement {
        int state;
        std::string word;
    };
    std::queue <queueElement> q;

    q.push({start_state, "\0"});

    int nr_word = 0;

    // The seen set behaves similar to a matrix seen, where seen[subword][node] = 1
    // if I have obtained the string subword having node as my current state.
    std::set<std::pair<std::string, int>> seen; // using unordered_set throws an error :(
    std::vector<std::string> accepted_words;

    while ((int)accepted_words.size() < total_words && !q.empty()) {
        queueElement current = q.front();
        q.pop();

        for (auto& map : transitions[current.state])
            for (auto& new_state : map.second) {
                if (isDeadState[new_state]) // I cannot reach any final state from new_state
                    continue;

                if (seen.find({current.word + map.first, new_state}) == seen.end())
                    // I have obtained the current string before, being on the same state
                    seen.insert({current.word + map.first, new_state});
                else    // it would be redundant to check if it is a solution | inset into the queue
                    continue;

                if ((int)accepted_words.size() < total_words && final_states.find(new_state) != final_states.end())
                    accepted_words.emplace_back(current.word + map.first);  // add to my solution

                q.push({new_state, current.word + map.first});
            }
    }

    // Sorting the answer vector lexicographically
    std::sort(accepted_words.begin(), accepted_words.end(),
        [](const std::string& a, const std::string& b) {    // lambda expression
        if (a.size() != b.size())
            return a.size() < b.size();
        return a < b;
    });

    return accepted_words;
}



