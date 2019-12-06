cmake_minimum_required(VERSION 3.15)
project(sudoku
        VERSION 0.1
        DESCRIPTION "Sudoku implementation with solvers"
        LANGUAGES CXX)


set(CMAKE_CXX_STANDARD 14)
# segfaults with optimisation level 3
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O2 -pthread")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -pthread")
set(BOOST_ROOT /home/joosep/boost_1_71_0new/)
set(Boost_INCLUDE_DIR /home/joosep/boost_1_71_0new/)
set(Boost_LIBRARY_DIR /home/joosep/boost_1_71_0new/stage/lib)
find_package(Boost 1.71.0 COMPONENTS program_options REQUIRED)

if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    link_directories(${Boost_LIBRARY_DIR})
endif ()

#cmake introduction
#https://www.youtube.com/watch?v=jt3meXdP-QI&t=7s

add_executable(main main.cpp)
add_executable(tests Sudoku_tests.cpp)
add_executable(solver-tests NaiveSolver_tests.cpp)
add_library(naive-solver SHARED NaiveSolver.h NaiveSolver.cpp)
add_library(sudoku SHARED Sudoku.h Sudoku.cpp)
target_link_libraries(tests sudoku)
target_link_libraries(naive-solver pthread)
target_link_libraries(solver-tests naive-solver sudoku)
# needed to add boost_program_options
target_link_libraries(main sudoku naive-solver boost_program_options)
