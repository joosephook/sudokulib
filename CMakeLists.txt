cmake_minimum_required(VERSION 3.15)
project(sudokulib
        VERSION 0.1
        DESCRIPTION "Sudoku implementation with solvers"
        LANGUAGES CXX)

set(BOOST_ROOT /home/joosep/boost_1_71_0new/)
find_package(Boost 1.71.0 COMPONENTS program_options unit_test_framework REQUIRED)

if (Boost_FOUND)
    message("Boost found...")
else ()
    message("Boost not found...")
endif ()

add_subdirectory(solverlib)
add_subdirectory(sudokulib)

add_executable(main main.cpp)
target_link_libraries(main sudokulib solverlib Boost::program_options)

message("Building release ${CMAKE_BUILD_TYPE}")
IF (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    target_compile_options(sudokulib PRIVATE -O0 -Wall -Wpedantic -Wextra)
    target_compile_options(solverlib PRIVATE -O0 -Wall -Wpedantic -Wextra)
    target_compile_options(main PRIVATE -O0 -Wall -Wpedantic -Wextra)
ELSEIF (${CMAKE_BUILD_TYPE} STREQUAL "Release")
    target_compile_options(main PUBLIC -O3)
ENDIF ()

