#include "DFA.hpp"

DFA::DFA() {}

DFA::DFA(std::vector <std::map <char, int>> transitions, int start_state, std::set <int> final_states): 
    transitions(transitions), start_state(start_state), final_states(final_states)
{}

std::ostream& operator << (std::ostream& out, const DFA& automaton)
{
    out << "Number of states = " << automaton.transitions.size() - 1 << "\n";
    for (int state = 1; state < automaton.transitions.size(); ++state) {
        for (auto& map : automaton.transitions[state]) {
            out << state << " --" << map.first << "--> " << map.second << '\n';
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
