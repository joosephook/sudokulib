//
// Created by joosep on 02/10/2019.
//

#ifndef SUDOKU_SUDOKU_H
#define SUDOKU_SUDOKU_H

#include <vector>
#include <set>
#include <string>

// valid - can make moves
// broken - cant make moves, but have free fields
// complete -cant make moves and have no free fields
// undetermined - God knows.
enum class SudokuState {
    valid, broken, complete, undetermined
};

class Sudoku {
private:
    std::vector<int> raw_sudoku;
    std::vector<std::vector<int>> rows;
    std::vector<std::vector<int>> columns;
    std::vector<std::vector<int>> squares;
    std::vector<std::set<int>> possibleMoves;
    SudokuState state;
public:
    SudokuState getState() const {
        return state;
    }

    const std::vector<std::set<int>> &getPossibleMoves() const {
        return possibleMoves;
    }

    explicit Sudoku(const std::string &s);

    Sudoku() = default;

    const std::vector<std::vector<int>> &getRows() const {
        return rows;
    }

    const std::vector<std::vector<int>> &getColumns() const {
        return columns;
    }

    const std::vector<int> &getRawSudoku() const {
        return raw_sudoku;
    }

    const std::vector<std::vector<int>> &getSquares() {
        return squares;
    }

    int numMoves();

    int freeFields();

    void updateRows(int idx);

    void updateColumns(int idx);

    void updateSquares(int idx);

    void updatePossibleMoves(int idx);

    void update();

    void updateState();

    SudokuState play(int idx, int number);

    bool isComplete();

    bool isBroken();

    //untested
    bool isFree(int idx);

    //TODO: replace with ostream operator
    //TODO: add istream operator to read from file
    void print();
};

#endif //SUDOKU_SUDOKU_H
