#include <iostream>
#include <fstream>
#include <tuple>
#include "Tree/Tree.h"
#include "Input/InputParser.h"
#include "Tree/TreeTest.h"

int main() {
    std::ifstream in("C:\\Users\\Piotr Szyma\\Documents\\Programowanie\\4 semestr\\AiSD\\L4\\in.txt");
    std::cin.rdbuf(in.rdbuf());
    Tree<int> tree;
    InputParser* inputParser = new InputParser();
    inputParser->getNumberOfInstructions();
    inputParser->getInput();

    std::vector<std::tuple<std::string, std::string>> commandsList = inputParser->getCommandsList();
    for (auto command: commandsList) {
        std::string commandName = std::get<0>(command);
        if (commandName.compare("insert") == 0) {
            int commandParameter = std::stoi(std::get<1>(command));
            tree.insert(commandParameter);
        } else if (commandName.compare("find") == 0) {
            int commandParameter = std::stoi(std::get<1>(command));
            std::cout << tree.find(commandParameter) << std::endl;
        } else if (commandName.compare("min") == 0) {
            try {
                std::cout << tree.min() << std::endl;
            } catch (std::exception &e) {
                std::cout << std::endl;
            }

        } else if (commandName.compare("max") == 0) {
            try {
                std::cout << tree.max() << std::endl;
            } catch (std::exception &e) {
                std::cout << std::endl;
            }

        } else if (commandName.compare("delete") == 0) {
            int commandParameter = std::stoi(std::get<1>(command));
            tree.remove(commandParameter);
        } else {
            try {
                tree.inorder();
                std::cout << std::endl;
            } catch (std::exception &e) {
                std::cout << std::endl;
            }
        }
    }

    TreeTest treeTest;
    treeTest.test();

    return 0;
}