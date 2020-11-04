//
// Created by joosep on 18/11/2019.
//

#ifndef SUDOKU_NAIVESOLVER_H
#define SUDOKU_NAIVESOLVER_H


#include "../sudokulib/sudokulib.h"
#include <deque>
#include <memory>
#include <optional>

class solverlib {
public:
    explicit solverlib() = default;

    static void solve(Sudoku &s);

    static Sudoku solveTask(Sudoku s);

    //untested
    static int singlePass(Sudoku &s);

    static std::optional<int> findSmallestBranch(Sudoku &s);

};


#endif //SUDOKU_NAIVESOLVER_H
