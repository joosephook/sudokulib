//
// Created by joosep on 03/10/2019.
//

#include "sudokulib.h"
#include <string>
#include <stdexcept>

void Sudoku::update() {
    for (int i = 0; i < 81; i++) {
        updatePossibleMoves(i);
    }
    updateState();
}

void Sudoku::updateState() {
    size_t free_fields = freeFields();
    size_t valid_moves = numMoves();

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

size_t Sudoku::freeFields() {
    size_t freeFields = 0;
    for(auto cell: raw_sudoku){
        if(0 == cell){
            freeFields++;
        }
    }
    return freeFields;
}

size_t Sudoku::numMoves() {
    size_t moves = 0;
    for(auto const &m : possibleMoves){
        moves += m.size();
    }
    return moves;
}

void Sudoku::updatePossibleMoves(int idx) {
    if (raw_sudoku[idx] != 0) {
        possibleMoves[idx].clear();
    }

    size_t column = idx % 9;
    size_t row = idx / 9;

    for(unsigned i = 0; i < 9; i++){
        size_t cursor = 9*row+i;
        possibleMoves[cursor].erase(raw_sudoku[idx]);
    }

    for(unsigned i = 0; i < 9; i++){
        size_t cursor = column+i*9;
        possibleMoves[cursor].erase(raw_sudoku[idx]);
    }

    size_t square_i = row / 3;
    size_t square_j = column / 3;
    for(unsigned i = 0; i < 3; i++){
        for(unsigned j = 0; j < 3; j++) {
            size_t cursor = 27*square_i + 3*square_j + j + 9*i;
            possibleMoves[cursor].erase(raw_sudoku[idx]);
        }
    }
}

bool Sudoku::isFree(int idx) {
    return raw_sudoku[idx] == 0;
}
