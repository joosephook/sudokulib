add_executable(solver solver.cpp)

IF (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    target_compile_options(solver PRIVATE -O0 -Wall -Wpedantic -Wextra)
ELSEIF (${CMAKE_BUILD_TYPE} STREQUAL "Release")
    target_compile_options(solver PUBLIC -O3)
ENDIF ()

