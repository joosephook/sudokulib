# Sudoku library [![Build Status](https://travis-ci.com/joosephook/sudokulib.svg?branch=master)](https://travis-ci.com/joosephook/sudokulib)

## Overview

This C++ project contains a Sudoku implementation that can be used to create and solve different sudokus.
In addition, it contains a multi-threaded implementation of a simple sudoku solver that uses a very simple algorithm for
solving sudokus.
The solver can be used from the command-line with many switches.

## Goal

The goal of this project is to learn to use 

* modern C++ features
* the build tool CMake
* a third-party library Boost
  * learn to use Boost::unit_test_framework, a library for writing unit tests
  * learn to use Boost::program_options, a convenient way of supplying your program command line arguments
* Travis CI for C++ builds and showing the last build status on GitHub
* valgrind's memcheck and cachegrind tools to profile the application
* CLion's code coverage to measure the extent of code tested by unit tests
* the profiling tools for C++ on Linux like `perf`

## Results

* use of modern CMake through employing targets
* each component lives in its own subdirectory with an appropriate CMakeLists.txt
* different compilation flags depending on build type
* ~99% lines covered by unit tests, with the exception of solver
* the solver can be configured by different command line flags
* the project uses Travis CI
* valgrind's memcheck identified no leaks in debug or release builds of the solver
* the 10k hardest sudokus in `5.txt` are solved in under 6s on a Ryzen 5 3600


## Future work
* implement a more advanced
* enhance the performance of the solver