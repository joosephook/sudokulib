cmake_minimum_required(VERSION 3.15)
project(sudokulib
        VERSION 0.1
        DESCRIPTION "Sudoku implementation with a multi-threaded solver"
        LANGUAGES CXX)

option(BUILD_TESTS "Build tests for solverlib and sudokulib" OFF)
option(BUILD_SOLVER "Build the command line sudoku solver executable" OFF)

if (BUILD_TESTS)
    find_package(Boost 1.71.0 COMPONENTS unit_test_framework REQUIRED)
endif ()

add_subdirectory(solverlib)
add_subdirectory(sudokulib)

if (BUILD_SOLVER)
    find_package(Boost 1.71.0 COMPONENTS program_options REQUIRED)
    add_subdirectory(solver)
endif ()


message("Building release ${CMAKE_BUILD_TYPE}")
