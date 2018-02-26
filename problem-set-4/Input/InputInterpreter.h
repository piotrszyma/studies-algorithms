//
// Created by thomp on 12.04.2017.
//
#include <string>

#ifndef L4_INPUTInterpreter_H
#define L4_INPUTInterpreter_H


class InputInterpreter {
public:
    InputInterpreter();
    std::tuple<std::string, std::string> interpret(std::string input);

private:
    std::tuple<std::string, std::string> concat(std::string input);
};

#endif //L4_INPUTInterpreter_H
