#include <iostream>
#include "Tree/Tree.h"
//#include "Input/InputParser.h"

int main() {
//    InputParser* inputParser = InputParser::getInputParser();
//    inputParser->getNumberOfInstructions();
//    inputParser->getInput();
//
    Tree<int> tree;
    tree.insert(10);
    tree.insert(12);
    tree.insert(9);
    tree.inorder();
    std::cout << tree.min() << std::endl;
    return 0;
}