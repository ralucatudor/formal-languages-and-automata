#ifndef NFA_HPP_INCLUDED
#define NFA_HPP_INCLUDED

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <set>

#include "DFA.hpp"

class NFA
{
    int start_state;        // q0
    std::set<int> final_states;   // F

    std::vector<std::map<char, std::set<int>>> transitions;   // delta

    static char lambda;     // simbolul asociat lui lambda
    static const std::string SIGMA;
public:
    NFA();
    NFA(int);

    friend std::istream& operator >> (std::istream&, NFA&);     // overloading >> operator
    friend std::ostream& operator << (std::ostream&, const NFA&);

    void convert_lambda_NFA_to_NFA();

    explicit operator DFA();
};


#endif // NFA_HPP_INCLUDED
