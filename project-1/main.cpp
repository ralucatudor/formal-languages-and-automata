#include <iostream>
#include <fstream>
#include "automaton.hpp"

int main()
{
    std::ifstream InputFile;
    InputFile.open("input.txt");

    std::ofstream OutputFile;
    OutputFile.open("output.txt");

    Automaton automaton;
    InputFile >> automaton;

    int nr_queries;
    InputFile >> nr_queries;

    for (int i = 0; i < nr_queries; i++){
        std::string s;
        InputFile >> s;
        OutputFile << automaton.isAccepted(s) << '\n';
    }

    auto x = automaton.smallestAcceptedWords(); // default value = 100

    for (auto i : x)
        OutputFile << i + "\n";

    InputFile.close();
    OutputFile.close();
}
