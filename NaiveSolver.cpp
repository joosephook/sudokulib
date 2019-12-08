//
// Created by joosep on 18/11/2019.
//

#include "NaiveSolver.h"
#include <deque>
#include <mutex>
#include <thread>
#include <cassert>
#include <iostream>

std::mutex sudoku_task_mutex;
std::mutex sudoku_solution_mutex;

void NaiveSolver::solveTask(std::deque<Sudoku> &tasks, std::deque<Sudoku> &solution) {
    Sudoku currentlySolving;
    bool needNew = true;

    while (solution.empty()) {
        while (needNew) {
            // deadlock if noone puts tasks in a queue anymore
            if (not solution.empty()) {
                return;
            }
            sudoku_task_mutex.lock();
            // if you don't get a task lock here, another thread can
            // empty the queue after you've checked that there are enough tasks in the queue.
            if (not tasks.empty()) {
                currentlySolving = std::move(tasks.front());
                tasks.pop_front();
                needNew = false;
            }
            sudoku_task_mutex.unlock();
        }


        int numPlays = 0;
        for (int i = 0; i < 81; i++) {
            if (currentlySolving.isFree(i) and (not currentlySolving.isBroken())) {
                auto moves = currentlySolving.getPossibleMoves()[i];
                auto numMoves = moves.size();

                if (numMoves == 1) {
                    auto onlyOption = *moves.begin();
                    currentlySolving.play(i, onlyOption);
                    numPlays++;
                }
            }
        }

        int leastPossibilities = 10;
        int branchIdx = -1;

        if (numPlays == 0) {
            auto moves = currentlySolving.getPossibleMoves();
            for (int i = 0; i < 81; i++) {
                if ((moves[i].size() > 1) and (moves[i].size() < leastPossibilities)) {
                    leastPossibilities = moves[i].size();
                    branchIdx = i;
                }
            }
        }

        if (currentlySolving.isComplete()) {
            // solved it
            sudoku_solution_mutex.lock();
            solution.push_back(currentlySolving);
            sudoku_solution_mutex.unlock();

            return;
        } else if (currentlySolving.isBroken()) {
            needNew = true;
        } else if (numPlays == 0) {
            assert(currentlySolving.getState() == SudokuState::valid);
            assert(branchIdx >= 0 and branchIdx < 81);
            for (int move : currentlySolving.getPossibleMoves()[branchIdx]) {
                // here we should def. copy
                Sudoku branch{currentlySolving};
                branch.play(branchIdx, move);

                if (branch.getState() == SudokuState::valid) {
                    sudoku_task_mutex.lock();
                    tasks.push_front(branch);
                    sudoku_task_mutex.unlock();
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
    // TODO: move semantics?
    // send solved sudoku back
    sudoku = std::move(solution.front());
}
