#include <iostream>

#include "board.h"
#include "move.h"

const char EMPTY = ' ';

Board::Board() {
    board = std::vector<std::vector<char>>(3, std::vector<char>(3, EMPTY));
}

void Board::display(bool withIndex) {
    
    #if defined(_WIN32)
        system("cls");
    #elif defined(__linux__)
        system("clear");
    #endif

    std::cout << "\n    Board    \t    Index    " << std::endl;
    std::cout << "-------------\t-------------" << std::endl;
    for (int i = 0; i < 3; ++i) {
        std::cout << "| ";
        for (int j = 0; j < 3; ++j) {
            std::cout << board[i][j] << " | ";
        }
        std::cout << "\t| ";
        for (int j = 0; j < 3; ++j) {
            std::cout << i * 3 + j + 1 << " | ";
        }
        std::cout << std::endl << "-------------\t" << "-------------" << std::endl;
    }
}

bool Board::isFull() {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] == EMPTY)
                return false;
        }
    }
    return true;
}

bool Board::isEmpty(int row, int col) {
    return board[row][col] == EMPTY;
}

void Board::placeMove(int row, int col, char playerSymbol) {
    board[row][col] = playerSymbol;
}

bool Board::checkWin(char playerSymbol) {
    // Check rows and columns
    for (int i = 0; i < 3; ++i) {
        if ((board[i][0] == playerSymbol && board[i][1] == playerSymbol && board[i][2] == playerSymbol) ||
            (board[0][i] == playerSymbol && board[1][i] == playerSymbol && board[2][i] == playerSymbol))
            return true;
    }

    // Check diagonals
    if ((board[0][0] == playerSymbol && board[1][1] == playerSymbol && board[2][2] == playerSymbol) ||
        (board[0][2] == playerSymbol && board[1][1] == playerSymbol && board[2][0] == playerSymbol))
        return true;

    return false;
}

std::vector<Move> Board::getAvailableMoves() {
    std::vector <Move> moves;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] == EMPTY) {
                moves.push_back({i, j});
            }
        }
    }
    return moves;
}

void Board::clearBoard() {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            board[i][j] = EMPTY;
        }
    }
}
