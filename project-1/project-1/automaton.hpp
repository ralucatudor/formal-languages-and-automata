#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <queue>
#include <algorithm>

class Automaton
{
    int start_state;
    std::unordered_set<int> final_states;
    std::vector<std::unordered_map<char, std::vector<int>>> transitions;
    std::vector<std::vector<int>> reverseTransitions;   // helper vector for constructing the isDeadState vector
    std::vector<bool> isDeadState;  // isDeadState[q] = 1 if I cannot reach a final state from q
public:
    Automaton();
    Automaton(int);
    friend std::istream& operator >> (std::istream&, Automaton&);   // overloading >> operator
    void markDeadStates();  // constructing the isDeadState vector
    bool isAccepted(const std::string);  /// NFA Membership
    std::vector<std::string> smallestAcceptedWords(int = 100) const;
};
