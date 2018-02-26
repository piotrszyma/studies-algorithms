#include "InputParser.h"
#include "InputInterpreter.h"
#include "../Tree/Tree.h"
#include <string>
#include <iostream>
#include <tuple>


InputParser::InputParser() {
    numberOfInstructions = 0;
}

void InputParser::getNumberOfInstructions() {
    std::string numberOfInstructionsString;
    std::getline(std::cin, numberOfInstructionsString);
    numberOfInstructions = stoi(numberOfInstructionsString);
}

void InputParser::getInput() {

    std::string line = "";
    std::tuple<std::string, std::string> command;
    for (int i = 0; i < numberOfInstructions; i++) {
        std::getline(std::cin, line);
        command = inputInterpreter->interpret(line);
        commandsList.push_back(command);
    }
}

std::vector<std::tuple<std::string, std::string>> InputParser::getCommandsList() {
    return commandsList;
};
