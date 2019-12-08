#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE NaiveSolver test

#include <boost/test/included/unit_test.hpp>
#include "../sudokulib/Sudoku.h"
#include "NaiveSolver.h"

//https://www.boost.org/doc/libs/1_71_0/libs/test/doc/html/index.html

BOOST_AUTO_TEST_CASE(naiveSolver_solveThreaded_single) {
    std::string string("123456789"
                       "456789123"
                       "789123456"
                       "234567891"
                       "567891234"
                       "891234567"
                       "345678912"
                       "678912345"
                       "000000000");

    BOOST_TEST(string.size() == 81);
    Sudoku incomplete(string);
    NaiveSolver solver;
    BOOST_CHECK(incomplete.isComplete() == false);
    solver.solveThreaded(incomplete, 1);
    BOOST_CHECK(incomplete.isComplete() == true);

    string = std::string("123456789"
                         "456789123"
                         "789123456"
                         "234567891"
                         "567891234"
                         "891234567"
                         "345678912"
                         "678912345"
                         "912345678");

    BOOST_TEST(string.size() == 81);
    Sudoku complete(string);
    BOOST_CHECK_NO_THROW(solver.solveThreaded(complete, 1));

    string = std::string("001700509573024106800501002700295018009400305652800007465080071000159004908007053");
    BOOST_TEST(string.size() == 81);
    incomplete = Sudoku(string);
    BOOST_CHECK(incomplete.isComplete() == false);
    solver.solveThreaded(incomplete, 1);
    BOOST_CHECK(incomplete.isComplete() == true);

    string = std::string("290500007700000400004738012902003064800050070500067200309004005000080700087005109");
    BOOST_TEST(string.size() == 81);
    incomplete = Sudoku(string);
    BOOST_CHECK(incomplete.isComplete() == false);
    solver.solveThreaded(incomplete, 1);
    BOOST_CHECK(incomplete.isComplete() == true);

    string = std::string("000075400000000008080190000300001060000000034000068170204000603900000020530200000");
    BOOST_TEST(string.size() == 81);
    incomplete = Sudoku(string);
    BOOST_CHECK(incomplete.isComplete() == false);
    solver.solveThreaded(incomplete, 1);
    BOOST_CHECK(incomplete.isComplete() == true);
}


BOOST_AUTO_TEST_CASE(naiveSolver_solveThreaded_multi) {
    std::string string("123456789"
                       "456789123"
                       "789123456"
                       "234567891"
                       "567891234"
                       "891234567"
                       "345678912"
                       "678912345"
                       "000000000");

    BOOST_TEST(string.size() == 81);
    Sudoku incomplete(string);
    NaiveSolver solver;
    BOOST_CHECK(incomplete.isComplete() == false);
    solver.solveThreaded(incomplete, 2);
    BOOST_CHECK(incomplete.isComplete() == true);

    string = std::string("123456789"
                         "456789123"
                         "789123456"
                         "234567891"
                         "567891234"
                         "891234567"
                         "345678912"
                         "678912345"
                         "912345678");

    BOOST_TEST(string.size() == 81);
    Sudoku complete(string);
    BOOST_CHECK_NO_THROW(solver.solveThreaded(complete, 2));

    string = std::string("001700509573024106800501002700295018009400305652800007465080071000159004908007053");
    BOOST_TEST(string.size() == 81);
    incomplete = Sudoku(string);
    BOOST_CHECK(incomplete.isComplete() == false);
    solver.solveThreaded(incomplete, 2);
    BOOST_CHECK(incomplete.isComplete() == true);

    string = std::string("290500007700000400004738012902003064800050070500067200309004005000080700087005109");
    BOOST_TEST(string.size() == 81);
    incomplete = Sudoku(string);
    BOOST_CHECK(incomplete.isComplete() == false);
    solver.solveThreaded(incomplete, 2);
    BOOST_CHECK(incomplete.isComplete() == true);

    string = std::string("000075400000000008080190000300001060000000034000068170204000603900000020530200000");
    BOOST_TEST(string.size() == 81);
    incomplete = Sudoku(string);
    BOOST_CHECK(incomplete.isComplete() == false);
    solver.solveThreaded(incomplete, 2);
    BOOST_CHECK(incomplete.isComplete() == true);
}
