#include <gtest/gtest.h>
#include <iostream>

#include "board.h"

const char PLAYER_X = 'X';
const char PLAYER_O = 'O';
const char EMPTY = ' ';

TEST(BoardTest, TestBoard) {
    Board board;
    std::vector<std::vector<char>> testBoard = board.getBoard();
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            ASSERT_EQ(testBoard[i][j], EMPTY);
        }
    }
}

TEST(BoardTest, TestMove) {
    Board board;
    
    board.placeMove(0, 0, PLAYER_X);
    board.placeMove(0, 1, PLAYER_O);
    board.placeMove(0, 2, PLAYER_X);
    board.placeMove(1, 0, PLAYER_O);
    board.placeMove(1, 1, PLAYER_X);

    std::vector<std::vector<char>> testBoard = board.getBoard();

    ASSERT_EQ(testBoard[0][0], PLAYER_X);
    ASSERT_EQ(testBoard[0][1], PLAYER_O);
    ASSERT_EQ(testBoard[0][2], PLAYER_X);
    ASSERT_EQ(testBoard[1][0], PLAYER_O);
    ASSERT_EQ(testBoard[1][1], PLAYER_X);
}