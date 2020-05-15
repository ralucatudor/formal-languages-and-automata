#include "RegularGrammar.hpp"

int main()
{
    std::ifstream inputFile;
    inputFile.open("input.txt");

    std::ofstream outputFile;
    outputFile.open("output.txt");

    RegularGrammar G;
    inputFile >> G;
    outputFile << "You introduced the following grammar:\n" << G;

    // Regular Grammar to NFA
    G.convertToLambdaFreeRegularGrammar();

    outputFile << "\nThe equivalent NFA is the following:\n";
    G.getNFA(outputFile);

    // explicit conversion
    NFA automaton = NFA(G);
    outputFile << "\nNFA:\n";
    outputFile << automaton << '\n';

    DFA dfa = DFA(automaton);

    outputFile << "After transformation of NFA to DFA:\n" << dfa << '\n';

    inputFile.close();
    outputFile.close();

    return EXIT_SUCCESS;
}
