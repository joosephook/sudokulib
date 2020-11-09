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
        updatePossibleMoves(idx);
        updateState();
        return state;
    } else {
        throw std::logic_error("number violated constraints on field [allowed moves are]:");
    }
}

int Sudoku::freeFields() {
    return std::count(raw_sudoku.cbegin(), raw_sudoku.cend(), 0);
}

int Sudoku::numMoves() {
    return std::accumulate(possibleMoves.cbegin(), possibleMoves.cend(), 0,
                           [](int a, const auto &b) { return a + b.size(); });
}

void Sudoku::updatePossibleMoves(int idx) {
    if (raw_sudoku[idx] != 0) {
        possibleMoves[idx].clear();
    }

    int column = idx % 9;
    int row = idx / 9;

    for(unsigned i = 0; i < 9; i++){
        int cursor = 9*row+i;
        possibleMoves[cursor].erase(raw_sudoku[idx]);
    }

    for(unsigned i = 0; i < 9; i++){
        int cursor = column+i*9;
        possibleMoves[cursor].erase(raw_sudoku[idx]);
    }

    int square_i = row / 3;
    int square_j = column / 3;
    for(unsigned i = 0; i < 3; i++){
        for(unsigned j = 0; j < 3; j++) {
            int cursor = 27*square_i + 3*square_j + j + 9*i;
            possibleMoves[cursor].erase(raw_sudoku[idx]);
        }
    }
}

bool Sudoku::isFree(int idx) {
    return raw_sudoku[idx] == 0;
}
