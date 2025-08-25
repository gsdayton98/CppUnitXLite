cmake_minimum_required(VERSION 3.25)
project(CppUnitXLite)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_INCLUDE_CURRENT_DIR_IN_INTERFACE ON)

set(CppUnitXLite_VERSION 1.4)

set(CMAKE_CXX_STANDARD 23)

add_library(CppUnitXLite STATIC CppUnitXLite.hpp CppUnitXLite.cpp)

set_property(TARGET CppUnitXLite PROPERTY VERSION ${CppUnitXLite_VERSION})
set_property(TARGET CppUnitXLite PROPERTY SOVERSION 1)
set_property(TARGET CppUnitXLite PROPERTY INTERFACE_CppUnitXLite_MAJOR_VERSION 1)
set_property(TARGET CppUnitXLite APPEND PROPERTY COMPATIBLE_INTERFACE_STRING CppUnitXLite_MAJOR_VERSION)

install(TARGETS CppUnitXLite EXPORT CppUnitXLiteTargets
        ARCHIVE  DESTINATION ${LIBDIR}
        LIBRARY  DESTINATION ${LIBDIR}
        INCLUDES DESTINATION ${INCLUDEDIR}
        PUBLIC_HEADER DESTINATION ${INCLUDEDIR})

install(FILES CppUnitXLite.hpp CppUnitXLite.cpp DESTINATION include)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
        "${CMAKE_CURRENT_BINARY_DIR}/CppUnitXLiteConfigVersion.cmake"
        VERSION ${CppUnitXLite_VERSION}
        COMPATIBILITY AnyNewerVersion)

export(EXPORT CppUnitXLiteTargets
        FILE "${CMAKE_CURRENT_BINARY_DIR}/CppUnitXLiteTargets.cmake"
        NAMESPACE CppUnitXLite::)
configure_file(cmake/CppUnitXLiteConfig.cmake
        "${CMAKE_CURRENT_BINARY_DIR}/CppUnitXLiteConfig.cmake"
        COPYONLY)

set(ConfigPackageLocation lib/cmake/CppUnitXLite)
install(EXPORT CppUnitXLiteTargets FILE CppUnitXLiteTargets.cmake NAMESPACE CppUnitXLite:: DESTINATION ${ConfigPackageLocation})
install(FILES cmake/CppUnitXLiteConfig.cmake
        "${CMAKE_CURRENT_BINARY_DIR}/CppUnitXLiteConfigVersion.cmake"
        DESTINATION ${ConfigPackageLocation})

add_subdirectory(test)