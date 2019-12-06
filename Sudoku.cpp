//
// Created by joosep on 03/10/2019.
//

#include "Sudoku.h"
#include <string>
#include <stdexcept>
#include <numeric>
#include <boost/math/special_functions/factorials.hpp>
#include <map>
#include <iostream>
#include <iterator>

Sudoku::Sudoku(const std::string &s) {
    state = SudokuState::undetermined;
    if (s.size() != 81) {
        //TODO: create custom exceptions to signal more useful information to the user about the failure conditions
        //TODO: write test for this case
        throw std::invalid_argument("Sudoku length must be 81 characters!");
    }
    assert(("The size of the sudoku string is 81", s.size() == 81));
    for (char character : s) {
        int nr = character - '0';
        if (nr < 0 || nr > 9) {
            throw std::out_of_range("faulty input: " + character);
        } else {
            raw_sudoku.push_back(nr);
        }
    }

    rows = std::vector<std::vector<int>>(9, std::vector<int>(9));
    columns = std::vector<std::vector<int>>(9, std::vector<int>(9));
    squares = std::vector<std::vector<int>>(9, std::vector<int>(9));
    possibleMoves = std::vector<std::set<int>>(81, std::set<int>{1, 2, 3, 4, 5, 6, 7, 8, 9});
    update();
}

void Sudoku::update() {
    for (int i = 0; i < 81; i++) {
        updateRows(i);
        updateColumns(i);
        updateSquares(i);
    }

    for (int i = 0; i < 81; i++) {
        updatePossibleMoves(i);
    }

    updateState();
}

void Sudoku::updateState() {
    int free_fields = freeFields();
    int valid_moves = numMoves();

    if (free_fields > 0 and valid_moves > 0) {
        state = SudokuState::valid;
    } else if (free_fields > 0 and valid_moves == 0) {
        state = SudokuState::broken;
    } else if (free_fields == 0 and valid_moves == 0) {
        state = SudokuState::complete;
    } else {
        state = SudokuState::undetermined;
    }
}

bool Sudoku::isComplete() {
    // sudoku is complete when we cannot make any more moves due to
    // all numbers being filled out or there being no more available places to play to
    return state == SudokuState::complete;
}

bool Sudoku::isBroken() {
    // sudoku is complete when we cannot make any more moves due to
    // all numbers being filled out or there being no more available places to play to
    return state == SudokuState::broken;
}

SudokuState Sudoku::play(int idx, int number) {
    if (idx < 0 or idx >= 81) {
        throw std::invalid_argument("idx out of allowed range (0, 81):" + std::to_string(idx));
    }
    if (number < 1 or number > 9) {
        throw std::invalid_argument("number out of allowed range [1, 9]:" + std::to_string(number));
    }

    if (isComplete()) {
        throw std::logic_error("Trying to play a complete sudoku");
    }

    if (possibleMoves[idx].count(number)) {
        raw_sudoku[idx] = number;
        update();
        return state;
    } else {
        throw std::logic_error("number violated constraints on field [allowed moves are]:");
    }
}

int Sudoku::freeFields() {
    return std::count(raw_sudoku.cbegin(), raw_sudoku.cend(), 0);
}

int Sudoku::numMoves() {
    int moves = 0;
    for (const auto &field : possibleMoves) {
        moves += field.size();
    }

    return moves;
}

void Sudoku::updateRows(int idx) {
    // update square, row and column and count free fields
    int column = idx % 9;
    int row = idx / 9;
    rows[row][column] = raw_sudoku[idx];
}

void Sudoku::updateColumns(int idx) {
    int column = idx % 9;
    int row = idx / 9;
    columns[column][row] = raw_sudoku[idx];
}

void Sudoku::updateSquares(int idx) {
    int column = idx % 9;
    int row = idx / 9;
    // column: x
    // row: y
    int square_i = row / 3;
    int square_j = column / 3;
    int square = 3 * square_i + square_j;
    // the position of the idx inside the square
    int in_square = idx - square_j * 3 - square_i * 27;
    in_square = in_square - (in_square / 9) * 6;

    squares[square][in_square] = raw_sudoku[idx];
}

void Sudoku::updatePossibleMoves(int idx) {
    int column = idx % 9;
    int row = idx / 9;
    int square = column / 3 + 3 * (row / 3);

    if (raw_sudoku[idx] != 0) {
        possibleMoves[idx].clear();
        return;
    }

    for (const auto i : rows[row]) {
        possibleMoves[idx].erase(i);
    }
    for (const auto i : columns[column]) {
        possibleMoves[idx].erase(i);
    }
    for (const auto i : squares[square]) {
        possibleMoves[idx].erase(i);
    }
}

bool Sudoku::isFree(int idx) {
    return raw_sudoku[idx] == 0;
}

void Sudoku::print() {
    std::ostream_iterator<int> coit(std::cout);
    std::copy(raw_sudoku.cbegin(), raw_sudoku.cend(), coit);
    std::cout << std::endl;
}
