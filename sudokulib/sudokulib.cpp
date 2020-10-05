//
// Created by joosep on 03/10/2019.
//

#include "sudokulib.h"
#include <string>
#include <stdexcept>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <numeric>

void Sudoku::update() {
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
    return state == SudokuState::complete;
}

bool Sudoku::isBroken() {
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
    if (isBroken()) {
        throw std::logic_error("Trying to play a broken sudoku");
    }

    if (possibleMoves[idx].count(number)) {
        raw_sudoku[idx] = number;
        update();
        return state;
    } else {
        throw std::logic_error("number violated constraints on field [allowed moves are]:" +
                               std::string(possibleMoves[idx].begin(), possibleMoves[idx].end()));
    }
}

int Sudoku::freeFields() {
    return std::count(raw_sudoku.cbegin(), raw_sudoku.cend(), 0);
}

int Sudoku::numMoves() {
    return std::accumulate(possibleMoves.cbegin(), possibleMoves.cend(), 0,
                           [](int a, const auto &b) { return a + b.size(); });
}

void Sudoku::updateRows(int idx) {
    // update square, row and column and count free fields
//    int column = idx % 9;
//    int row = idx / 9;
//    rows[row][column] = raw_sudoku[idx];
}

void Sudoku::updateColumns(int idx) {
//    int column = idx % 9;
//    int row = idx / 9;
//    columns[column][row] = raw_sudoku[idx];
}

void Sudoku::updateSquares(int idx) {
//    int column = idx % 9;
//    int row = idx / 9;
    // column: x
    // row: y
//    int square_i = row / 3;
//    int square_j = column / 3;
//    int square = 3 * square_i + square_j;
    // the position of the idx inside the square
//    int in_square = idx - square_j * 3 - square_i * 27;
//    in_square = in_square - (in_square / 9) * 6;

//    squares[square][in_square] = raw_sudoku[idx];
}

void Sudoku::updatePossibleMoves(int idx) {
    int column = idx % 9;
    int row = idx / 9;

    if (raw_sudoku[idx] != 0) {
        possibleMoves[idx].clear();
        return;
    }
    int square_i = row / 3;
    int square_j = column / 3;

    for(unsigned i = 0; i < 9; i++){
        possibleMoves[idx].erase(raw_sudoku[9*row+i]);
    }

    for(unsigned i = 0; i < 9; i++){
        possibleMoves[idx].erase(raw_sudoku[column+i*9]);
    }

    for(unsigned i = 0; i < 3; i++){
        for(unsigned j = 0; j < 3; j++) {
            possibleMoves[idx].erase(raw_sudoku[27*square_i + 3*square_j + j + 9*i]);
        }
    }
}

bool Sudoku::isFree(int idx) {
    return raw_sudoku[idx] == 0;
}
