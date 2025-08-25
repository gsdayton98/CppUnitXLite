project(cpp_unit_test_xlite_test)
cmake_minimum_required(VERSION 3.25)
cmake_minimum_required(VERSION 3.25)
include_directories(${cpp_unit_test_xlite_test_SOURCE_DIR}/../..)

add_executable(CppUnitXLiteTests CppUnitXLiteTests.hpp CppUnitXLiteTests.cpp)
target_link_libraries(CppUnitXLiteTests CppUnitXLite)
add_executable(NoMacroTests NoMacroTests.cpp ../CppUnitXLite.hpp)
target_link_libraries(NoMacroTests CppUnitXLite)

