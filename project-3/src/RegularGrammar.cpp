#include "RegularGrammar.hpp"

std::string RegularGrammar::lambda = "$";

RegularGrammar::RegularGrammar() {}

std::istream& operator >> (std::istream& in, RegularGrammar& grammar)
{
    std::string lhs, rhs;

    while (in >> lhs >> rhs) {
        if (rhs == grammar.lambda) {        
            grammar.hasLambdaProduction.insert(lhs);
            continue;
        }
        // copy all lambda-free productions 
        grammar.productions[lhs].insert(rhs);
    }

    return in;
}

std::ostream& operator << (std::ostream& out, const RegularGrammar& grammar)
{
    for (auto& production : grammar.productions) {
        std::string lhs = production.first;
        out << lhs << " : ";
        for (auto& rhs : production.second) {
            out << rhs << " ";
        }   
        if (grammar.hasLambdaProduction.find(lhs) != grammar.hasLambdaProduction.end()) {
            out << grammar.lambda;
        }
        out << '\n';
    }
    return out;
}

void RegularGrammar::convertToLambdaFreeRegularGrammar() 
{
    for (auto& production : productions) {
        std::string lhs = production.first;
        // if N->lambda is in G, copy every rule in which N appears on the right hand side both with and without N
        for (auto& rhs : production.second) {
            if (rhs.size() > 1 && isupper(rhs[rhs.size() - 1])) {   // Assume that we are given a left-linear grammar
                std::string nonTerminal = rhs.substr(rhs.size() - 1);
                if (hasLambdaProduction.find(nonTerminal) != hasLambdaProduction.end()) {
                    std::string str = rhs.substr(0, rhs.size() - 1);
                    productions[lhs].insert(str);
                }
            }
        }
    }
    // Note: assume that S is the start symbol.
    // if S->lambda was in the original set of rules, add a new start symbol S1 in G', add the rule S1->lambda
    // and copy all the production rules with S on the left hand side to ones with S' on the left hand side. 
    if (hasLambdaProduction.find("S") != hasLambdaProduction.end())
    {
        hasLambdaProduction.clear();
        productions["S1"] = productions["S"];
        productions["S1"].insert(lambda);
        hasLambdaProduction.insert("S1");
    }
    else {
        hasLambdaProduction.clear();
    }
}