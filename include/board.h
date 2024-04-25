#ifndef BOARD_H
#define BOARD_H

#include <vector>

#include "move.h"

class Board {

private:
    std::vector<std::vector<char>> board;

public:
    Board();
    Board(std::vector<std::vector<char>> board);
    ~Board();
    std::vector<std::vector<char>> getBoard();
    void setBoard(std::vector<std::vector<char>> board);
    bool isFull();
    bool isEmpty(int row, int col);
    void placeMove(int row, int col, char player);
    bool checkWin(char player);
    std::vector<Move> getAvailableMoves();
    std::vector<int> getFirstAvailableMove();
    std::vector<int> getMoveUp(std::vector<int> position);
    std::vector<int> getMoveDown(std::vector<int> position);
    std::vector<int> getMoveLeft(std::vector<int> position);
    std::vector<int> getMoveRight(std::vector<int> position);
    void clearBoard();
};

#endif // BOARD_H
