//
// Created by joosep on 02/10/2019.
//

#ifndef SUDOKU_SUDOKU_H
#define SUDOKU_SUDOKU_H

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
    unsigned int moves = 0;
    size_t n_moves = 0;

public:
    Moves () {
        moves = 0
                | (1 << 1)
                | (1 << 2)
                | (1 << 3)
                | (1 << 4)
                | (1 << 5)
                | (1 << 6)
                | (1 << 7)
                | (1 << 8)
                | (1 << 9);
        n_moves = 9;
    }

    void erase(int move){
//        moves &= ~(1 << move);
//        n_moves -= ((moves & (1 << move)) >> move);
        if((1 << move) & moves){
            moves ^= (1 << move);
            n_moves -= 1;
        }
    }

    void clear(){
        moves = 0;
        n_moves = 0;
    }

    size_t count(int move){
        return moves & (1 << move);
    }

    size_t size() const {
        return n_moves;
    }

    std::array<int, 10> getMoves () {
        std::array<int, 10> m;
        m.fill(0);
        for(size_t i = 1; i < m.size(); i++){
            if(moves & (1 << i)){
                m[i] = i;
            }
        }
        return m;
    }
};

class Sudoku {
private:
    SudokuState state;
    std::array<int, 81> raw_sudoku;
    std::array<Moves, 81> possibleMoves;
public:
    explicit Sudoku(const std::string &s) : state(SudokuState::undetermined),
                                            raw_sudoku{0}
                                            {
        if (s.size() != 81) {
            throw std::invalid_argument("Sudoku length must be 81 characters!");
        }

        for(unsigned i = 0; i < 81; i++){
            char character = s[i];
            int nr = character - '0';
            if (nr < 0 || nr > 9) {
                throw std::out_of_range("Faulty input: " + std::string{character});
            } else {
                raw_sudoku[i] = nr;
            }
        }
        update();
    };

    void update();

    Sudoku() = default;

    const std::array<int, 81> &getRawSudoku() const {
        return raw_sudoku;
    }

    const std::array<Moves, 81> &getPossibleMoves() const {
        return possibleMoves;
    }

    size_t numMoves();

    size_t freeFields();

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
