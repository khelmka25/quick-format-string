cmake_minimum_required(VERSION 3.20)
project(QFString_project)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# internal library
add_subdirectory(${CMAKE_SOURCE_DIR}/src)

# Catch2
add_subdirectory(${CMAKE_SOURCE_DIR}/deps/Catch2)

option(RUN_TESTS OFF)

if (RUN_TESTS)
    enable_testing()
    add_subdirectory(${CMAKE_SOURCE_DIR}/tests)
endif(RUN_TESTS)