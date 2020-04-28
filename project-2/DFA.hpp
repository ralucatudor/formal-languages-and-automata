#ifndef DFA_HPP_INCLUDED
#define DFA_HPP_INCLUDED

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>

class DFA
{
    int start_state;
    std::set<int> final_states;

    std::vector<std::map<char, int>> transitions;
public:
    DFA();
    DFA(std::vector <std::map <char, int>>, int, std::set <int>);

    friend std::istream& operator >> (std::istream&, DFA&);   
    friend std::ostream& operator << (std::ostream&, const DFA&);

    void removeUnreachableStates();

    void minimize();
};

#endif // DFA_HPP_INCLUDED
