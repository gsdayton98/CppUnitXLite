cmake_minimum_required(VERSION 3.25)
project(cpp_unit_xlite)

set(BINDIR bin)
set(LIBDIR lib)
set(INCLUDEDIR include)

set(CMAKE_CXX_STANDARD 23)

add_library(cpp_unit_xlite STATIC CppUnitXLite.hpp CppUnitXLite.cpp)

install(TARGETS ${PROJECT_NAME} EXPORT cpp_unit_xlite
        ARCHIVE  DESTINATION ${LIBDIR}
        LIBRARY  DESTINATION ${LIBDIR}
        PUBLIC_HEADER DESTINATION ${INCLUDEDIR})
install(EXPORT cpp_unit_xlite DESTINATION share/cpp_unit_xlite/cmake)
export(TARGETS ${PROJECT_NAME} FILE cpp_unit_xlite.cmake)

add_subdirectory(test)