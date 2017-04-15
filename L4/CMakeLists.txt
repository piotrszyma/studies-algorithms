cmake_minimum_required(VERSION 3.6)
project(L4)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        main.cpp
        Tree/Tree.h
        Tree/Tree.cpp
        Tree/TreeNode.h
        Tree/TreeNode.cpp
        Input/InputInterpreter.h
        Input/InputInterpreter.cpp
        Input/InputParser.h
        Input/InputParser.cpp
        )
add_executable(L4 ${SOURCE_FILES})