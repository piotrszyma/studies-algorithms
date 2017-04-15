cmake_minimum_required(VERSION 3.5)
project(AiSD)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES L1Z2.c)
add_executable(AiSD ${SOURCE_FILES})