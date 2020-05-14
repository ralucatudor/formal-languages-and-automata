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
    // outputFile << "Lalala:\n" << G;



    inputFile.close();
    outputFile.close();

    return EXIT_SUCCESS;
}
