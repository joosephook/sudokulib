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
    int nThreads;

    // Declare the supported options.
    po::options_description desc("Allowed options");
    desc.add_options()
            ("help", "produce help message")
            ("file", po::value<std::string>(&sudoku_file), "set sudokulib file to solve")
            ("threads", po::value<int>(&nThreads)->default_value(1), "number of threads to use for solvin")
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
        std::cout << "No sudokulib file specified, exiting." << std::endl;
        return EXIT_FAILURE;
    }

    std::string sudoku_line;
    std::ifstream infile(sudoku_file);

    auto t1 = std::chrono::high_resolution_clock::now();
    while (std::getline(infile, sudoku_line)) {
        Sudoku s(sudoku_line);
        solverlib::solveThreaded(s, nThreads);
        if (vm.count("print")) {
            std::cout << s << std::endl;
//            s.print();
        }
    }
    auto t2 = std::chrono::high_resolution_clock::now();

    if (vm.count("benchmark")) {
        auto time = std::chrono::duration<double, std::milli>{t2 - t1};
        std::cout << sudoku_file << " took " << time.count() << " milliseconds." << std::endl;
    }

    return EXIT_SUCCESS;
}