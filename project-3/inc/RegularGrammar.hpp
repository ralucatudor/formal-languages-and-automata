#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <set>

class RegularGrammar 
{
    static std::string lambda;  
    
    std::map <std::string, std::set <std::string>> productions;
    std::set <std::string> hasLambdaProduction;
    // Note: I use std::string for the lhs because I might have a non-terminal containing more than 1 character
    // i.e. S1, D0

public:
    RegularGrammar();

    friend std::istream& operator >> (std::istream&, RegularGrammar&);     // overloading >> operator
    friend std::ostream& operator << (std::ostream&, const RegularGrammar&);

    void convertToLambdaFreeRegularGrammar();
};