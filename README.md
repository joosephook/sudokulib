# Sudoku library [![Build Status](https://travis-ci.com/joosephook/sudokulib.svg?branch=master)](https://travis-ci.com/joosephook/sudokulib)

## Overview

This C++ project contains a Sudoku implementation that can be used to create and solve different sudokus.
In addition, it contains a multi-threaded implementation of a simple sudoku solver that uses a very simple algorithm for
solving sudokus.
The solver can be used from the command-line with many switches.

## Goal

The goal of this project is to learn to use 

* modern C++ features
* try and write multi-threaded code
* the build tool CMake
* using a third-party library Boost
  * learn to use Boost::unit_test_framework, a library for writing unit tests
  * learn to use Boost::program_options, a convenient way of supplying your program command line arguments
* using Travis CI for C++ builds and showing the last build status on GitHub
* using valgrind's memcheck and cachegrind tools to profile the application
* using CLion's code coverage to measure the extent of code tested by unit tests

## Results

* use of modern CMake through employing targets
* each component lives in its own subdirectory with an appropriate CMakeLists.txt
* different compilation flags depending on build type
* ~99% lines covered by unit tests, with the exception of solver
* the solver can be configured by different command line flags
* the solver is multi-threaded
* the project uses Travis CI
* valgrind's memcheck identified no leaks in debug or release builds of the solver


## Future work

* implement a more complicated solver
* enhance the performance of the solver
* decrease the memory consumption of the solver and sudokulib
* create documentation for the libraries