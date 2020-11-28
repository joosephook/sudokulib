//
// Created by joosep on 02/10/2019.
//

#ifndef SUDOKU_SUDOKU_H
#define SUDOKU_SUDOKU_H

#include <vector>
#include <set>
#include <string>
#include <stdexcept>
#include <iterator>
#include <algorithm>
#include <array>

// valid - can make moves
// broken - cant make moves, but have free fields
// complete -cant make moves and have no free fields
// undetermined - God knows.
enum class SudokuState {
    valid, broken, complete, undetermined
};

class Moves {
    std::array<int, 10> moves;
    size_t n_moves;

public:
    Moves () {
        moves = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        n_moves = 9;
    }

    void erase(int move){
        if(moves[move]){
            moves[move] = 0;
            n_moves -= 1;
        }
    }

    void clear(){
        moves = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        n_moves = 0;
    }

    size_t count(int move){
        return moves[move] == move;
    }

    size_t size() const {
        return n_moves;
    }

    const std::array<int, 10> &getMoves () {
        return moves;
    }
};

class Sudoku {
private:
    SudokuState state;
    std::vector<int> raw_sudoku;
    std::vector<Moves> possibleMoves;
public:
    explicit Sudoku(const std::string &s) : state(SudokuState::undetermined),
                                            raw_sudoku(std::vector<int>()),
                                            possibleMoves(std::vector<Moves>(81)){

        if (s.size() != 81) {
            throw std::invalid_argument("Sudoku length must be 81 characters!");
        }

        raw_sudoku.reserve(81);
        for (char character : s) {
            int nr = character - '0';
            if (nr < 0 || nr > 9) {
                throw std::out_of_range("Faulty input: " + std::string{character});
            } else {
                raw_sudoku.push_back(nr);
            }
        }
        update();
    };

    void update();

    Sudoku() = default;

    const std::vector<int> &getRawSudoku() const {
        return raw_sudoku;
    }

    const std::vector<Moves> &getPossibleMoves() const {
        return possibleMoves;
    }

    int numMoves();

    int freeFields();

    SudokuState getState() const {
        return state;
    }

    SudokuState play(int idx, int number);

    bool isComplete();

    bool isBroken();

    void updatePossibleMoves(int idx);

    void updateState();

    bool isFree(int idx);
};

std::ostream &operator<<(std::ostream &os, const Sudoku &obj) {
    std::ostream_iterator<int> coit(os);
    std::copy(obj.getRawSudoku().cbegin(), obj.getRawSudoku().cend(), coit);
    return os;
}

#endif //SUDOKU_SUDOKU_H
