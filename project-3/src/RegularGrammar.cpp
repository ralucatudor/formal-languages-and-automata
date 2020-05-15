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


void RegularGrammar::getNFA(std::ostream& out) 
{
    int nr_states = productions.size() + 1; // + 1 from another terminal state D

    out << nr_states << '\n';

    std::string start_state;
    if (hasLambdaProduction.find("S1") != hasLambdaProduction.end()) {
        // then S1 is my start state
        start_state = "S1";
    }
    else {
        start_state = "S";
    }    
    
    int nr_transitions = 0;
    for (auto& production : productions) {
        nr_transitions += production.second.size();
    }

    if (start_state == "S1") {
        nr_transitions -= 1;        // S1->lambda will not result in a transition
    }

    out << nr_transitions << '\n';

    std::set <std::string> final_states;
    // The final states will be those from the hasLambdaProduction set
    final_states = hasLambdaProduction;
    // plus state D
    final_states.insert("D");


    for (auto& production : productions) {
        std::string lhs = production.first;
        for (auto& rhs : production.second) {
            if (rhs == lambda) {
                continue;
            }
            if (islower(rhs[rhs.size() - 1])) {
                out << lhs << " D " << rhs << '\n';
            }
            else {
                // for every production AaB in G, add a transition from state A to state B labelled with terminal a; 
                out << lhs << " " << rhs.substr(rhs.size() - 1) << " " << rhs.substr(0, rhs.size() - 1) << '\n';
            }
        }
    }

    out << start_state << '\n';

    
    out << final_states.size() << '\n';
    for (auto& final_state : final_states) {
        out << final_state << ' ';
    }
    out << '\n';
}


RegularGrammar::operator NFA()
{
    // For this conversion to NFA, I'll assume that the rhs of any production is either a or aB, 
    // where a in SIGMA (union lambda, of course), not SIGMA*! (as these definitions are equivalent)
    // In this way, I'll maintain the rule state1 --character--> state2 from the NFA class
    // (not state1 --string--> state2)

    std::map <std::string, int> stateIndex;
    unsigned stateCount = 1;
    for (auto& production : productions) {
        std::string lhs = production.first;
        stateIndex[lhs] = stateCount;
        stateCount++;
    }
    // add another terminal state D
    stateIndex["D"] = stateCount;

    int start_state;
    if (hasLambdaProduction.find("S1") != hasLambdaProduction.end()) {
        // then S1 is my start state
        start_state = stateIndex["S1"];
    }
    else {
        start_state = stateIndex["S"];
    }

    std::set<int> final_states; 
    // The final states will be those from the hasLambdaProduction set
    for (auto& lhs : hasLambdaProduction) {
        final_states.insert(stateIndex[lhs]);
    }
    // plus state D
    final_states.insert(stateIndex["D"]);
    
   
    std::vector<std::map<char, std::set<int>>> transitions(stateCount + 1); 
    for (auto& production : productions) {
        std::string lhs = production.first;
        for (auto& rhs : production.second) {
            if (rhs == lambda) {
                continue;
            }
            if (rhs.size() == 1) {
                transitions[stateIndex[lhs]][rhs[0]].insert(stateIndex["D"]);
            }
            else {
                transitions[stateIndex[lhs]][rhs[0]].insert(stateIndex[rhs.substr(1)]);
            }
        }
    }

    return NFA(transitions, start_state, final_states);
}
