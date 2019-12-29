cmake_minimum_required(VERSION 3.0)
project(sudokulib
        VERSION 0.1
        DESCRIPTION "Sudoku implementation with a multi-threaded solver"
        LANGUAGES CXX)

option(BUILD_TESTS "Build tests for solverlib and sudokulib" OFF)
option(BUILD_SOLVER "Build the command line sudoku solver executable" OFF)
option(COPY_SUDOKUS "Copy the sudoku files to the build directory")

if (BUILD_TESTS)
    find_package(Boost 1.65.0 COMPONENTS unit_test_framework REQUIRED)
endif ()

add_subdirectory(solverlib)
add_subdirectory(sudokulib)

if (BUILD_SOLVER)
    find_package(Boost 1.65.0 COMPONENTS program_options REQUIRED)
    add_subdirectory(solver)
endif ()


message("Building release ${CMAKE_BUILD_TYPE}")

if (COPY_SUDOKUS)
    file(COPY sudokus DESTINATION ${CMAKE_BINARY_DIR})
endif ()

