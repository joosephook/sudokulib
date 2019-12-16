add_library(sudokulib SHARED sudokulib.h sudokulib.cpp)
if (BUILD_TESTS)
    add_executable(sudokulib-tests sudokulib-tests.cpp)
    target_link_libraries(sudokulib-tests sudokulib Boost::unit_test_framework)
    target_include_directories(sudokulib-tests PUBLIC ${Boost_INCLUDE_DIRS})
endif ()

IF (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    target_compile_options(sudokulib PRIVATE -O0 -Wall -Wpedantic -Wextra)
ENDIF ()

