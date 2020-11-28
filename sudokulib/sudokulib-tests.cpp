#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN
#define BOOST_TEST_MODULE Sudoku test

#include <boost/test/included/unit_test.hpp>
#include <boost/test/tools/output_test_stream.hpp>
#include "sudokulib.h"

//https://www.boost.org/doc/libs/1_71_0/libs/test/doc/html/index.html

BOOST_AUTO_TEST_CASE(Sudoku_faulty) {
    std::string faulty("123456789"
                       "n00000000"
                       "000000000"
                       "000000000"
                       "000000000"
                       "000000000"
                       "000000000"
                       "000000000"
                       "000000000");
    BOOST_TEST(faulty.size() == 81);
    BOOST_CHECK_THROW(new Sudoku(faulty), std::out_of_range);
}

BOOST_AUTO_TEST_CASE(Sudoku_empty) {
    std::string faulty("");
    BOOST_CHECK_THROW(new Sudoku(faulty), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(Sudoku_normal) {
    std::string string("123456789"
                       "000000000"
                       "000000000"
                       "000000000"
                       "000000000"
                       "000000000"
                       "000000000"
                       "000000000"
                       "000000000");

    BOOST_TEST(string.size() == 81);
    Sudoku sudoku(string);
    std::vector<int> raw_sudoku(81, 0);
    BOOST_TEST(sudoku.getRawSudoku() != raw_sudoku);
    for (int i = 0; i < 9; i++) {
        raw_sudoku[i] = i + 1;
    }
    BOOST_TEST(sudoku.getRawSudoku() == raw_sudoku);
}

BOOST_AUTO_TEST_CASE(getRawSudoku) {
    std::string string("111111111"
                       "222222222"
                       "333333333"
                       "444444444"
                       "555555555"
                       "666666666"
                       "777777777"
                       "888888888"
                       "999999999");

    BOOST_TEST(string.size() == 81);
    Sudoku sudoku(string);
    std::vector<int> numbers;
    int num = 1;
    for (int i = 0; i < 81; i++) {
        numbers.push_back(num);
        if (i and ((i + 1) % 9 == 0)) {
            num++;
        }
    }

    BOOST_TEST(numbers == sudoku.getRawSudoku());
}

BOOST_AUTO_TEST_CASE(getPossibleMoves) {
    std::string zeros("000000000"
                      "000000000"
                      "000000000"
                      "000000000"
                      "000000000"
                      "000000000"
                      "000000000"
                      "000000000"
                      "000000000");
    Sudoku empty(zeros);

    std::array<int, 10> all_moves{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto possible_moves = empty.getPossibleMoves();

    for (int i = 0; i < 81; i++) {
        BOOST_TEST(possible_moves[i].getMoves() == all_moves);
    }


    std::string complete("123456789"
                         "456789123"
                         "789123456"
                         "234567891"
                         "567891234"
                         "891234567"
                         "345678912"
                         "678912345"
                         "912345678");

    BOOST_TEST(complete.size() == 81);

    Sudoku done(complete);

    std::array<int, 10> no_moves{0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    possible_moves = done.getPossibleMoves();
    for (int i = 0; i < 81; i++) {
        BOOST_TEST(possible_moves[i].getMoves() == no_moves);
    }

    std::string almost("123456789"
                       "456789123"
                       "789123456"
                       "234567891"
                       "567891234"
                       "891234567"
                       "345678912"
                       "678912345"
                       "000000000");
    Sudoku doable(almost);

    possible_moves = doable.getPossibleMoves();

    for (int i = 72; i < 81; i++) {
        std::array<int, 10> moves{0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        moves[done.getRawSudoku()[i]] = done.getRawSudoku()[i];
        BOOST_TEST(possible_moves[i].getMoves() == moves);
    }
}

BOOST_AUTO_TEST_CASE(numMoves) {
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
    BOOST_TEST(incomplete.numMoves() == 9);

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
    BOOST_TEST(complete.numMoves() == 0);

    string = std::string("000000000"
                         "000000000"
                         "000000000"
                         "000000000"
                         "000000000"
                         "000000000"
                         "000000000"
                         "000000000"
                         "000000000");

    BOOST_TEST(string.size() == 81);
    Sudoku empty(string);
    BOOST_TEST(empty.numMoves() == 81 * 9);


    string = std::string("123456789"
                         "456789123"
                         "789123456"
                         "234567891"
                         "567891234"
                         "891234567"
                         "345678912"
                         "000000000"
                         "000000000");

    BOOST_TEST(string.size() == 81);
    incomplete = Sudoku(string);
    BOOST_TEST(incomplete.numMoves() == 36);
}

BOOST_AUTO_TEST_CASE(freeFields) {
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
    BOOST_TEST(incomplete.freeFields() == 9);

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
    BOOST_TEST(complete.freeFields() == 0);

    string = std::string("000000000"
                         "000000000"
                         "000000000"
                         "000000000"
                         "000000000"
                         "000000000"
                         "000000000"
                         "000000000"
                         "000000000");

    BOOST_TEST(string.size() == 81);
    Sudoku empty(string);
    BOOST_TEST(empty.freeFields() == 81);


    string = std::string("123456789"
                         "456789123"
                         "789123456"
                         "234567891"
                         "567891234"
                         "891234567"
                         "345678912"
                         "000000000"
                         "000000000");

    BOOST_TEST(string.size() == 81);
    incomplete = Sudoku(string);
    BOOST_TEST(incomplete.freeFields() == 18);
}

BOOST_AUTO_TEST_CASE(getState) {
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
    // note: boost_test fails with scoped enums because it can't print them
    // use boost_check or implement operator<<
    BOOST_CHECK(incomplete.getState() == SudokuState::valid);

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
    BOOST_CHECK(complete.getState() == SudokuState::complete);

    string = std::string("000000000"
                         "000000000"
                         "000000000"
                         "000000000"
                         "000000000"
                         "000000000"
                         "000000000"
                         "000000000"
                         "000000000");

    BOOST_TEST(string.size() == 81);
    Sudoku empty(string);
    BOOST_CHECK(empty.getState() == SudokuState::valid);

    string = std::string("123456789"
                         "456789123"
                         "789123456"
                         "234567891"
                         "567891234"
                         "891234567"
                         "345678912"
                         "679012348"
                         "912345670");

    BOOST_TEST(string.size() == 81);
    Sudoku broken(string);
    BOOST_CHECK(broken.getState() == SudokuState::broken);
}

BOOST_AUTO_TEST_CASE(isComplete) {
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
    // note: boost_test fails with scoped enums because it can't print them
    // use boost_check or implement operator<<
    BOOST_CHECK(not incomplete.isComplete());

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
    BOOST_CHECK(complete.isComplete());

    string = std::string("000000000"
                         "000000000"
                         "000000000"
                         "000000000"
                         "000000000"
                         "000000000"
                         "000000000"
                         "000000000"
                         "000000000");

    BOOST_TEST(string.size() == 81);
    Sudoku empty(string);
    BOOST_CHECK(not empty.isComplete());
}

BOOST_AUTO_TEST_CASE(isBroken) {
    std::string string("123456789"
                       "456789123"
                       "789123456"
                       "234567891"
                       "567891234"
                       "891234567"
                       "345678912"
                       "679012348"
                       "912345670");

    BOOST_TEST(string.size() == 81);
    Sudoku broken(string);
    BOOST_CHECK(broken.isBroken());

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
    BOOST_CHECK(not complete.isBroken());
}

BOOST_AUTO_TEST_CASE(isFree) {
    std::string string("290500007700000400004738012902003064800050070500067200309004005000080700087005109");
    Sudoku sudoku(string);
    for (int i = 0; i < 81; i++) {
        BOOST_TEST(sudoku.isFree(i) == (string[i] == '0'));
    }
}

BOOST_AUTO_TEST_CASE(play) {
    std::string string("123456789"
                       "456789123"
                       "789123456"
                       "234567891"
                       "567891234"
                       "891234567"
                       "345678912"
                       "678912345"
                       "912345000");

    BOOST_TEST(string.size() == 81);
    /// 78 79 80
    /// 6 7 8
    Sudoku incomplete(string);
    BOOST_CHECK_THROW(incomplete.play(78, 0), std::invalid_argument);
    BOOST_CHECK_THROW(incomplete.play(78, -1), std::invalid_argument);
    BOOST_CHECK_THROW(incomplete.play(78, 10), std::invalid_argument);

    BOOST_CHECK_THROW(incomplete.play(-1, 1), std::invalid_argument);
    BOOST_CHECK_THROW(incomplete.play(81, 1), std::invalid_argument);

    BOOST_CHECK_THROW(incomplete.play(78, 5), std::logic_error);


    BOOST_CHECK_THROW(incomplete.play(77, 5), std::logic_error);
    incomplete.play(78, 6);
    incomplete.play(79, 7);
    incomplete.play(80, 8);

    BOOST_CHECK_THROW(incomplete.play(80, 8), std::logic_error);

    string = std::string("123456789"
                         "456789123"
                         "789123456"
                         "234567891"
                         "567891234"
                         "891234567"
                         "345678912"
                         "679012348"
                         "912345670");

    BOOST_TEST(string.size() == 81);
    Sudoku broken(string);
    BOOST_CHECK_THROW(broken.play(80, 9), std::logic_error);
}

BOOST_AUTO_TEST_CASE(operator_out) {
    boost::test_tools::output_test_stream output;
    std::string string("123456789"
                       "456789123"
                       "789123456"
                       "234567891"
                       "567891234"
                       "891234567"
                       "345678912"
                       "678912345"
                       "912345000");

    BOOST_TEST(string.size() == 81);
    /// 78 79 80
    /// 6 7 8
    Sudoku incomplete(string);
    output << incomplete;
    BOOST_TEST(output.is_equal(string));
}

