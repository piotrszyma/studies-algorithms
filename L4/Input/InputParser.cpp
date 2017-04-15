//
// Created by thomp on 12.04.2017.
//

#include "InputParser.h"
#include "InputInterpreter.h"
#include <string>
#include <iostream>
#include <tuple>

InputParser::InputParser() {
    inputInterpreter = new InputInterpreter();
}

InputParser& InputParser::getInputParser() {
    if (!inputParser) {
        inputParser = new InputParser();
    }
    return inputParser;
}

void InputParser::getNumberOfInstructions() {
    std::cin >> numberOfInstructions;
}

void InputParser::getInput() {
//    if (numberOfInstructions == nullptr) {
//        //TODO: throw new exception
//    }

    std::string line;
    std::tuple<std::string, std::string> command;

    for (int i = 0; i < numberOfInstructions; i++) {
        std::getline(std::cin, line);
        command = inputInterpreter->interpret(line);
        commandsList.push_back(command);
    }
}
