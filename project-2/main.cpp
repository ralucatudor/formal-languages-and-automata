#include "NFA.hpp"

int main()
{
    std::ifstream inputFile;
    inputFile.open("input.txt");

    std::ofstream outputFile;
    outputFile.open("output.txt");

    NFA automaton;
    inputFile >> automaton;

    outputFile << "The read automaton:\n" << automaton << '\n';

    automaton.convert_lambda_NFA_to_NFA();

    outputFile << "After lambda-Transition Removal:\n" << automaton << '\n';

    DFA dfa = DFA(automaton);

    outputFile << "After transformation of NFA to DFA:\n" << dfa << '\n';

    dfa.minimize();

    outputFile << "After DFA minimization:\n" << dfa << '\n';

    inputFile.close();
    outputFile.close();

    return EXIT_SUCCESS;
}
