project(Calc)

cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 14)

include_directories(Classes)

add_executable(Calc main.cpp Classes/calculator.cpp Classes/treeNode.cpp Classes/treePrinter.cpp)