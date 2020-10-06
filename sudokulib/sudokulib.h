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

// valid - can make moves
// broken - cant make moves, but have free fields
// complete -cant make moves and have no free fields
// undetermined - God knows.
enum class SudokuState {
    valid, broken, complete, undetermined
};

class Sudoku {
private:
    SudokuState state;
    std::vector<int> raw_sudoku;
    std::vector<std::vector<int>> squares;
    std::vector<std::set<int>> possibleMoves;
public:
    explicit Sudoku(const std::string &s) : state(SudokuState::undetermined),
                                            raw_sudoku(std::vector<int>()),
                                            possibleMoves(std::vector<std::set<int>>(81,
                                                                                     std::set<int>{1, 2, 3, 4, 5, 6, 7,
                                                                                                   8, 9})) {

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

    Sudoku() = default;

    const std::vector<int> &getRawSudoku() const {
        return raw_sudoku;
    }

    const std::vector<std::set<int>> &getPossibleMoves() const {
        return possibleMoves;
    }


    int numMoves();

    int freeFields();

    SudokuState getState() const {
        return state;
    }

    bool isComplete();

    bool isBroken();

    SudokuState play(int idx, int number);

    bool isFree(int idx);

    //untested or tested implicitly
    void update();

    void updateState();

    void updatePossibleMoves(int idx);

};

std::ostream &operator<<(std::ostream &os, const Sudoku &obj) {
    std::ostream_iterator<int> coit(os);
    std::copy(obj.getRawSudoku().cbegin(), obj.getRawSudoku().cend(), coit);
    return os;
}

#endif //SUDOKU_SUDOKU_H
