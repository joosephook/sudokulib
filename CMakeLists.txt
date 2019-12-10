cmake_minimum_required(VERSION 3.15)
project(sudokulib
        VERSION 0.1
        DESCRIPTION "Sudoku implementation with solvers"
        LANGUAGES CXX)


#set(CMAKE_CXX_STANDARD 14)


set(Boost_INCLUDE_DIR /home/joosep/boost_1_71_0new/)
set(Boost_LIBRARY_DIR /home/joosep/boost_1_71_0new/stage/lib)
set(BOOST_ROOT /home/joosep/boost_1_71_0new/)
find_package(Boost 1.71.0 COMPONENTS program_options unit_test_framework REQUIRED)

if (Boost_FOUND)
    message("Boost found...")
    include_directories(${Boost_INCLUDE_DIRS})
    link_directories(${Boost_LIBRARY_DIR})
endif ()

add_library(naive-solver SHARED solverlib/NaiveSolver.h solverlib/NaiveSolver.cpp)
target_link_libraries(naive-solver pthread)

add_library(sudokulib SHARED sudokulib/Sudoku.h sudokulib/Sudoku.cpp)

add_executable(tests sudokulib/Sudoku_tests.cpp)
target_link_libraries(tests sudokulib boost_unit_test_framework)

add_executable(solver-tests solverlib/NaiveSolver_tests.cpp)
target_link_libraries(solver-tests naive-solver sudokulib boost_unit_test_framework)

# needed to add boost_program_options
add_executable(main main.cpp)
target_link_libraries(main sudokulib naive-solver boost_program_options)

message("Building release ${CMAKE_BUILD_TYPE}")
IF (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    target_compile_options(main PUBLIC -O0)
ELSEIF (${CMAKE_BUILD_TYPE} STREQUAL "Release")
    target_compile_options(main PUBLIC -O3)
ENDIF ()

