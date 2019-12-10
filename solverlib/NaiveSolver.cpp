//
// Created by joosep on 18/11/2019.
//

#include "NaiveSolver.h"
#include <deque>
#include <mutex>
#include <thread>
#include <cassert>

std::mutex sudoku_task_mutex;
std::mutex sudoku_solution_mutex;

int NaiveSolver::singlePass(Sudoku &sudoku) {
    int numPlays = 0;
    for (int i = 0; i < 81; i++) {
        if (sudoku.isFree(i) and (not sudoku.isBroken())) {
            auto moves = sudoku.getPossibleMoves()[i];
            auto numMoves = moves.size();

            if (numMoves == 1) {
                auto onlyOption = *moves.begin();
                sudoku.play(i, onlyOption);
                numPlays++;
            }
        }
    }
    return numPlays;
}

int NaiveSolver::findSmallestBranch(Sudoku &sudoku) {
    unsigned int leastPossibilities = 10;
    int branchIdx = -1;

    auto moves = sudoku.getPossibleMoves();
    for (int i = 0; i < 81; i++) {
        if (leastPossibilities == 2) {
            break;
        }

        if ((moves[i].size() > 1) and (moves[i].size() < leastPossibilities)) {
            leastPossibilities = moves[i].size();
            branchIdx = i;
        }
    }

    return branchIdx;
}

void NaiveSolver::solveTask(std::deque<Sudoku> &tasks, std::deque<Sudoku> &solution) {
    Sudoku currentlySolving;
    bool needNew = true;

    while (solution.empty()) {
        while (needNew) {
            // if we don't check for solutions here, can get stuck in endless loop
            if (not solution.empty()) {
                return;
            }
            std::lock_guard<std::mutex> lck{sudoku_task_mutex};
            // if you don't get the task lock here, another thread can empty the queue
            // after you've checked that there are enough tasks in the queue, causing a segfault
            if (not tasks.empty()) {
                currentlySolving = std::move(tasks.front());
                tasks.pop_front();
                needNew = false;
            }
        }

        int playsMade = singlePass(currentlySolving);
        int branchIdx = -1;

        if (playsMade == 0) {
            branchIdx = findSmallestBranch(currentlySolving);
        }

        if (currentlySolving.isComplete()) {
            // solved it
            std::lock_guard<std::mutex> lck{sudoku_solution_mutex};
            solution.push_back(currentlySolving);

            return;
        } else if (currentlySolving.isBroken()) {
            needNew = true;
        } else if (playsMade == 0) {
            assert(currentlySolving.getState() == SudokuState::valid);
            assert(branchIdx >= 0 and branchIdx < 81);
            for (int move : currentlySolving.getPossibleMoves()[branchIdx]) {
                // here we should def. copy
                Sudoku branch{currentlySolving};
                branch.play(branchIdx, move);

                if (branch.getState() == SudokuState::valid) {
                    std::lock_guard<std::mutex> lck{sudoku_task_mutex};
                    tasks.push_front(branch);
                }
            }
            needNew = true;
        }
    }
}

void NaiveSolver::solveThreaded(Sudoku &sudoku, int nThreads) {
    std::deque<Sudoku> tasks{sudoku}, solution;
    std::vector<std::thread> threads;

    for (int i = 0; i < nThreads; i++) {
        threads.emplace_back(&solveTask, std::ref(tasks), std::ref(solution));
    }

    for (auto &thread : threads) {
        if (thread.joinable()) {
            thread.join();
        }
    }
    sudoku = std::move(solution.front());
}
