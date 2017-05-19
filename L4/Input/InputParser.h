#ifndef L4_INPUTPARSER_H
#define L4_INPUTPARSER_H

#include <vector>
#include "InputInterpreter.h"
#include "../Tree/Tree.h"


class InputParser {
    InputInterpreter* inputInterpreter;
    std::vector<std::tuple<std::string, std::string>> commandsList;
    int numberOfInstructions;

public:

    InputParser();

    void getNumberOfInstructions();

    void getInput();

    std::vector<std::tuple<std::string, std::string>> getCommandsList();
};


#endif //L4_INPUTPARSER_H
