cmake_minimum_required(VERSION 3.25)
project(cpp_unit_xlite)

set(CMAKE_CXX_STANDARD 23)

add_library(cpp_unit_xlite STATIC CppUnitXLite.hpp CppUnitXLite.cpp)

add_subdirectory(test)