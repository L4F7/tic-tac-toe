#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <map>
#include <vector>

#include "move.h"

class Board {

private:
    std::vector<std::vector<char>> board;

public:
    Board();
    void display();
    bool isFull();
    bool isEmpty(int row, int col);
    void placeMove(int row, int col, char player);
    bool checkWin(char player);
    std::vector<Move> getAvailableMoves();
    void clearBoard();
};

#endif // BOARD_H
