project(Calc)

cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE Debug)

include_directories(Classes)

add_executable(Calc main.cpp Classes/Parser.cpp Classes/TreeNode.cpp Classes/TreePrinter.cpp)