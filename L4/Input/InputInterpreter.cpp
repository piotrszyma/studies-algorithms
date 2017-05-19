#include <string>
#include <tuple>
#include <iostream>
#include "InputInterpreter.h"

std::tuple<std::string, std::string> InputInterpreter::interpret(std::string input) {
    std::tuple<std::string, std::string> command = this->concat(input);
    return command;
}

InputInterpreter::InputInterpreter() {};

std::tuple<std::string, std::string> InputInterpreter::concat(std::string input) {
    unsigned int commandSpacePosition = input.find_first_of(" ");
    std::tuple<std::string, std::string> commandTuple;
    std::string command;
    std::string parameter;
    if (commandSpacePosition == std::string::npos) {
        command = input;
        parameter = "";
        commandTuple = std::make_tuple(command, parameter);

    } else {
        command = input.substr(0, commandSpacePosition);
        parameter = input.substr(commandSpacePosition + 1);
        commandTuple = std::make_tuple(command, parameter);
    }

    return commandTuple;
}

