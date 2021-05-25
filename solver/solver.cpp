#include <iostream>
#include "../solverlib/solverlib.h"
#include "../sudokulib/sudokulib.h"

#include <string>
#include <chrono>
#include <ostream>
#include <fstream>
#include <boost/program_options.hpp>

namespace po = boost::program_options;

int main(int argc, char *argv[]) {
    std::string sudoku_file;

    // Declare the supported options.
    po::options_description desc("Allowed options");
    desc.add_options()
            ("help", "produce help message")
            ("file", po::value<std::string>(&sudoku_file), "set sudokulib file to solve")
            ("benchmark", "benchmark solution time")
            ("print", "print solution");

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("help")) {
        std::cout << desc << "\n";
        return EXIT_SUCCESS;
    }

    if (sudoku_file.empty()) {
        std::cout << "No sudoku file specified, exiting." << std::endl;
        return EXIT_FAILURE;
    }

    std::string sudoku_line;
    std::ifstream infile(sudoku_file);

    double total_time = 0;
    double n_sudoku = 0;
    std::vector<Sudoku> sudokus;
    sudokus.reserve(10000);
    while (std::getline(infile, sudoku_line)) {
        sudokus.emplace_back(sudoku_line);
    }
    for(auto &s: sudokus){
        auto t1 = std::chrono::high_resolution_clock::now();
        solverlib::solve(s);
        auto t2 = std::chrono::high_resolution_clock::now();
        total_time += std::chrono::duration<double, std::milli>{t2 - t1}.count();
        n_sudoku += 1.0;
        if (vm.count("print")) {
            std::cout << s << std::endl;
        }
    }

    if (vm.count("benchmark")) {
        std::cout << "Solved " << n_sudoku << " sudokus in ";
        std::cout << total_time << " ms, " << total_time/n_sudoku << " ms per sudoku";
    }

    return EXIT_SUCCESS;
}