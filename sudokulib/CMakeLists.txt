add_library(sudokulib SHARED Sudoku.h Sudoku.cpp)

add_executable(tests Sudoku_tests.cpp)
target_link_libraries(tests sudokulib Boost::unit_test_framework)
target_include_directories(tests PUBLIC ${Boost_INCLUDE_DIRS})

IF (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    target_compile_options(sudokulib PRIVATE -O0 -Wall -Wpedantic -Wextra)
ENDIF ()

