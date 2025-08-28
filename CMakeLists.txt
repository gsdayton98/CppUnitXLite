cmake_minimum_required(VERSION 3.25)
project(CppUnitXLite VERSION 1.4.0 LANGUAGES CXX)

include(GNUInstallDirs)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_INCLUDE_CURRENT_DIR_IN_INTERFACE ON)

set(CMAKE_CXX_STANDARD 23)

add_library(CppUnitXLite STATIC CppUnitXLite.hpp CppUnitXLite.cpp)

add_library(CppUnitXLiteInterface INTERFACE)
target_include_directories(CppUnitXLiteInterface INTERFACE "${CppUnitXLite_INCLUDE_DIRS}")


target_include_directories(CppUnitXLite PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:include>)

# defines to CMake libCppUnitXLite.a and CppUnitXLite::Lib,
set_target_properties(CppUnitXLite PROPERTIES
    OUTPUT_NAME CppUnitXLite
    EXPORT_NAME Lib)

# this allows CppUnitXLite to be uses as a subdirectory (as in a git module) or a package.
add_library(CppUnitXLite::Lib ALIAS CppUnitXLite)

install(TARGETS CppUnitXLite EXPORT CppUnitXLiteTargets
        ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(FILES CppUnitXLite.hpp CppUnitXLite.cpp DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")

install(EXPORT CppUnitXLiteTargets
        FILE CppUnitXLiteTargets.cmake
        NAMESPACE CppUnitXLite::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/CppUnitXLite)

include(CMakePackageConfigHelpers)
set(CppUnitXLite_INCLUDE_DIRS "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_INCLUDEDIR}")
set(CppUnitXLite_LIBDIR "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}" )
set(CppUnitXLite_LIBRARIES "CppUnitXLite")

configure_package_config_file("cmake/CppUnitXLiteConfig.cmake.in"
        "CppUnitXLiteConfig.cmake"
        INSTALL_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/CppUnitXLite"
        PATH_VARS CppUnitXLite_INCLUDE_DIRS CppUnitXLite_LIBDIR CppUnitXLite_LIBRARIES
        INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

write_basic_package_version_file(
        "CppUnitXLiteConfigVersion.cmake"
        VERSION ${CppUnitXLite_VERSION}
        COMPATIBILITY AnyNewerVersion)

install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/CppUnitXLiteConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/CppUnitXLiteConfigVersion.cmake"
        DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/CppUnitXLite")

add_subdirectory(test)