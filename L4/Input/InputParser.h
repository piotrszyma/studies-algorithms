#ifndef L4_INPUTPARSER_H
#define L4_INPUTPARSER_H

#include <vector>
#include "InputInterpreter.h"


class InputParser {
    static InputParser* inputParser;
    InputInterpreter* inputInterpreter;
    std::vector<std::tuple<std::string, std::string>> commandsList;
    int numberOfInstructions;

    InputParser();

    InputParser(const InputParser &);

    InputParser &operator=(const InputParser &);

public:
    static InputParser &getInputParser();

    void getNumberOfInstructions();

    void getInput();

    void executeInterpretedCommands();
};


#endif //L4_INPUTPARSER_H
