add_executable(CppUnitXLiteTests CppUnitXLiteTests.hpp CppUnitXLiteTests.cpp)
target_link_libraries(CppUnitXLiteTests CppUnitXLite)
target_include_directories(CppUnitXLiteTests PUBLIC "${PROJECT_SOURCE_DIR}/")

add_executable(NoMacroTests NoMacroTests.cpp)
target_link_libraries(NoMacroTests CppUnitXLite)
target_include_directories(NoMacroTests PUBLIC "${PROJECT_SOURCE_DIR}")

