//
// Created by joosep on 18/11/2019.
//

#include "solverlib.h"
#include <deque>
#include <cassert>
#include <algorithm>


int solverlib::singlePass(Sudoku &sudoku) {
    int numPlays = 0;

    for (int i = 0; i < 81; i++) {
        if (sudoku.isFree(i) and (not sudoku.isBroken())) {
            auto possibleMoves = sudoku.getPossibleMoves()[i];
            auto allMoves = possibleMoves.getMoves();
            if (possibleMoves.size() == 1) {
                auto onlyOption = *std::find_if(allMoves.cbegin(), allMoves.cend(), [](int i){return i != 0;});
                sudoku.play(i, onlyOption);
                numPlays++;
            }
        }
    }
    return numPlays;
}

std::optional<int> solverlib::findSmallestBranch(Sudoku &sudoku) {
    std::optional<int> branchIdx;
    unsigned int leastPossibilities = 10;

    auto moves = sudoku.getPossibleMoves();
    for (int i = 0; i < 81; i++) {
        if ((moves[i].size() > 1) and (moves[i].size() < leastPossibilities)) {
            leastPossibilities = moves[i].size();
            branchIdx = i;
        }
    }

    return branchIdx;
}

Sudoku solverlib::solveTask(Sudoku s) {
    Sudoku currentlySolving = s;
    std::deque<Sudoku> tasks = {currentlySolving};

    for (;;) {
        int playsMade = singlePass(currentlySolving);

        if (currentlySolving.isComplete()) {
            return currentlySolving;
        } else if (currentlySolving.isBroken()) {
            currentlySolving = tasks.front();
            tasks.pop_front();
        } else if (playsMade == 0) {
            std::optional<int> branchIdx = findSmallestBranch(currentlySolving);
            assert(branchIdx);
            assert(currentlySolving.getState() == SudokuState::valid);
            auto possibleMoves = currentlySolving.getPossibleMoves()[branchIdx.value()];
            auto allMoves = possibleMoves.getMoves();
            for (int move : allMoves) {
                if(move == 0) continue;

                // here we should definitely copy
                Sudoku branch{currentlySolving};
                branch.play(branchIdx.value(), move);

                if (branch.getState() == SudokuState::valid) {
                    tasks.push_front(branch);
                }
            }
            currentlySolving = tasks.front();
            tasks.pop_front();
        }
    }
}

void solverlib::solve(Sudoku &sudoku){
    sudoku = solveTask(sudoku);
}
