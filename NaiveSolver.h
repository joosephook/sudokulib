//
// Created by joosep on 18/11/2019.
//

#ifndef SUDOKU_NAIVESOLVER_H
#define SUDOKU_NAIVESOLVER_H


#include "Sudoku.h"
#include <deque>
#include <memory>

class NaiveSolver {
public:
    explicit NaiveSolver() = default;

    void solve(Sudoku &s);

    void solveThreaded(Sudoku &s, int n);

    bool static solveTask(std::deque<Sudoku> &tasks, std::deque<Sudoku> &solution);
};


#endif //SUDOKU_NAIVESOLVER_H
