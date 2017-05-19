//
// Created by Piotr Szyma on 19.04.2017.
//

#include <fstream>
#include <random>
#include <iostream>
#include <algorithm>
#include "TreeTest.h"
#include "../Tree/Tree.h"

thread_local std::mt19937 gen{std::random_device{}()};

template<typename T>
T random(T min, T max) {
    return std::uniform_int_distribution<T>{min, max}(gen);
}

TreeTest::TreeTest() {};

void TreeTest::test() {
    Tree<int> tree;
    std::ofstream averageOutput("average.txt");
    std::ofstream maxOutput("max.txt");
    std::ofstream minOutput("min.txt");

    auto engine = std::default_random_engine{};
    int numberOfTestsOnAverage = 20000;
    int maxTreeSize = 30000;
    double minOperations, averageOperations, maxOperations;
    double averageOperationsSum = 0;

    for (int i = 1; i <= maxTreeSize; i++) {
        tree.insert(i);
    }

    for (int treeSize = 10; treeSize <= maxTreeSize; treeSize += 10) {
        tree.resetNumberOfOperationsInFind();
        tree.find(0);
        minOperations = tree.getNumberOfOperationsInFind();
        tree.resetNumberOfOperationsInFind();
        tree.find(treeSize);
        maxOperations = tree.getNumberOfOperationsInFind();
        minOutput << treeSize << " " << minOperations << "\n";
        maxOutput << treeSize << " " << maxOperations << "\n";
    }

    for (int treeSize = 10; treeSize <= maxTreeSize; treeSize += 10) {
        std::vector<int> elements;
        for (int i = 1; i <= treeSize; i++) {
            elements.push_back(i);
        }
        std::shuffle(std::begin(elements), std::end(elements), engine);
        Tree<int> randomTree;

        for (auto item: elements) {
            randomTree.insert(item);
        }
        averageOperationsSum = 0;
        for (int i = 0; i < numberOfTestsOnAverage; i++) {
            randomTree.resetNumberOfOperationsInFind();
            randomTree.find(random(0, treeSize));
            averageOperationsSum += randomTree.getNumberOfOperationsInFind();
        }
        averageOperations = averageOperationsSum / numberOfTestsOnAverage;
        averageOutput << treeSize << " " << averageOperations << "\n";
    }


    //rozmiar od 10 do 1000 znajdź różny element

    //rozmiar od 10 do 1000 znajdź 100 razy pierwszy element

    //rozmiar od 1 do 1000 znajdź 100 razy ostatni element
};