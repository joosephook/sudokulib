add_executable(solver solver.cpp)
target_link_libraries(solver solverlib sudokulib Boost::program_options)

IF (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    target_compile_options(solver PRIVATE -O0 -Wall -Wpedantic -Wextra -g -fprofile-arcs -ftest-coverage --coverage)
    target_link_libraries(solver gcov)
    target_link_options(solver PRIVATE -fprofile-arcs -lgcov)
ELSEIF (${CMAKE_BUILD_TYPE} STREQUAL "Release")
    target_compile_options(solver PUBLIC -O3)
ENDIF ()

