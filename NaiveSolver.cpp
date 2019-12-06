//
// Created by joosep on 18/11/2019.
//

#include "NaiveSolver.h"
#include <deque>
#include <mutex>
#include <thread>
#include <cassert>

void NaiveSolver::solve(Sudoku &sudoku) {
    std::deque<Sudoku> stack{sudoku};
    Sudoku currentlySolving = stack.front();
    while (not currentlySolving.isComplete()) {
        int leastPossibilities = 9;
        bool mustBranch = true;
        int branchIdx = -1;

        loop:
        for (int i = 0; i < 81; i++) {
            if (not currentlySolving.isFree(i)) {
                continue;
            }
            auto moves = currentlySolving.getPossibleMoves()[i];
            auto numMoves = moves.size();

            if (numMoves == 1) {
                auto onlyOption = *moves.begin();
                currentlySolving.play(i, onlyOption);
                if (currentlySolving.isBroken()) {
                    stack.pop_front();
                    currentlySolving = stack.front();
                    goto loop;
                }
                mustBranch = false;
                continue;
            }

            if (numMoves and numMoves < leastPossibilities) {
                leastPossibilities = numMoves;
                branchIdx = i;
            }
        }

        if (currentlySolving.isComplete()) {
            return;
        } else if (mustBranch) {
            for (int move : currentlySolving.getPossibleMoves()[branchIdx]) {
                Sudoku branch = Sudoku(currentlySolving);
                branch.play(branchIdx, move);
                stack.push_back(branch);
            }
            stack.pop_front();
            currentlySolving = stack.front();
        }
    }
}

std::mutex sudoku_task_mutex;
std::mutex sudoku_solution_mutex;

bool NaiveSolver::solveTask(std::deque<Sudoku> &tasks, std::deque<Sudoku> &solution) {
    Sudoku currentlySolving;
    start:

    bool taskReceived = false;
    while (not taskReceived) {
        if (not solution.empty()) {
            return false;
        }
        sudoku_task_mutex.lock();
        // if you don't get a task lock here, another thread can
        // empty the queue after you've checked that there are enough tasks in the queue.
        if (not tasks.empty()) {
            currentlySolving = std::move(tasks.front());
            tasks.pop_front();
            taskReceived = true;
        }
        sudoku_task_mutex.unlock();
    }

    while (not currentlySolving.isComplete()) {
        int leastPossibilities = 9;
        bool mustBranch = true;
        int branchIdx = -1;

        for (int i = 0; i < 81; i++) {
            if (not currentlySolving.isFree(i)) {
                continue;
            }
            auto moves = currentlySolving.getPossibleMoves()[i];
            auto numMoves = moves.size();

            if (numMoves == 1) {
                auto onlyOption = *moves.begin();
                currentlySolving.play(i, onlyOption);
                if (currentlySolving.isBroken()) {
                    goto start;
                }
                mustBranch = false;
                continue;
            }

            if (numMoves and numMoves < leastPossibilities) {
                leastPossibilities = numMoves;
                branchIdx = i;
            }
        }

        if (currentlySolving.isComplete()) {
            // solved it
            sudoku_solution_mutex.lock();
            solution.push_back(currentlySolving);
            sudoku_solution_mutex.unlock();

            return true;
        } else if (mustBranch) {
            assert(currentlySolving.getState() == SudokuState::valid);
            assert(branchIdx >= 0 and branchIdx < 81);
            sudoku_task_mutex.lock();
            for (int move : currentlySolving.getPossibleMoves()[branchIdx]) {
                // here we should def. copy
                Sudoku branch{currentlySolving};
                branch.play(branchIdx, move);

                if (branch.getState() == SudokuState::valid) {
                    tasks.push_front(branch);
                }
            }
            sudoku_task_mutex.unlock();
            goto start;
        }
    }
}

void NaiveSolver::solveThreaded(Sudoku &sudoku, int nThreads) {
    std::deque<Sudoku> tasks{sudoku}, solution;
    std::vector<std::thread> threads;

    for (int i = 0; i < nThreads; i++) {
        threads.push_back(std::thread{&solveTask, std::ref(tasks), std::ref(solution)});
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
