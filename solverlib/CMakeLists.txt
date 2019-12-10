add_library(solverlib SHARED NaiveSolver.h NaiveSolver.cpp)
target_link_libraries(solverlib pthread)

add_executable(solver-tests NaiveSolver_tests.cpp)
target_link_libraries(solver-tests solverlib sudokulib Boost::unit_test_framework)
target_include_directories(solver-tests PUBLIC ${Boost_INCLUDE_DIRS})


IF (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    target_compile_options(solverlib PRIVATE -O0 -Wall -Wpedantic -Wextra)
ENDIF ()
