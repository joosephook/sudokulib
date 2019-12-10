//
// Created by joosep on 18/11/2019.
//

#ifndef SUDOKU_NAIVESOLVER_H
#define SUDOKU_NAIVESOLVER_H


#include "../sudokulib/Sudoku.h"
#include <deque>
#include <memory>

class NaiveSolver {
public:
    explicit NaiveSolver() = default;

    static void solveThreaded(Sudoku &s, int n);

    static void solveTask(std::deque<Sudoku> &tasks, std::deque<Sudoku> &solution);

    static int singlePass(Sudoku &s);

    static int findSmallestBranch(Sudoku &s);

};


#endif //SUDOKU_NAIVESOLVER_H
