#include "board.h"
#include "move.h"

const char EMPTY = ' ';
const char PLAYER_X = 'X';
const char PLAYER_O = 'O';

Board::Board() {
    board = std::vector<std::vector<char>>(3, std::vector<char>(3, EMPTY));
}

void Board::display() {

#if defined(_WIN32)
    system("cls");
#elif defined(__linux__)
    system("clear");
#endif

    std::map<char, std::vector<std::string>> board_map = {
        {'X', {"█ █", " █ ", "█ █"}},
        {'O', {" █ ", "█ █", " █ "}},
        {' ', {"   ", "   ", "   "}}};

    for (int i = 0; i < 13; i++) {

        if (i == 0)
            std::cout << "    ╔═════╦═════╦═════╗    ╔═════╦═════╦═════╗\n";
        else if (i == 12)
            std::cout << "    ╚═════╩═════╩═════╝    ╚═════╩═════╩═════╝\n";
        else if (i % 4 == 0)
            std::cout << "    ╠═════╬═════╬═════╣    ╠═════╬═════╬═════╣\n";
        else {

            for (int j = 0; j < 7; j++) {

                std::string color = "\033[31m";
                std::string colorEnd = "\e[0m";

                if (j == 0) {
                    std::cout << "    ║ ";
                } else if (j == 6) {
                    std::cout << " ║";
                    std::cout << "    ";
                    if (i % 2 == 0) {
                        int row_index = (i - 1) / 4;
                        int col_index = (j - 1) / 2;

                        std::string firstColor = "\033[39m";
                        std::string secondColor = "\033[39m";
                        std::string thirdColor = "\033[39m";

                        if (board[row_index][col_index - 2] == PLAYER_O)
                            firstColor = "\033[94m\033[9m";
                        else if (board[row_index][col_index - 2] == PLAYER_X)
                            firstColor = "\033[91m\033[9m";

                        if (board[row_index][col_index - 1] == PLAYER_O)
                            secondColor = "\033[94m\033[9m";
                        else if (board[row_index][col_index - 1] == PLAYER_X)
                            secondColor = "\033[91m\033[9m";

                        if (board[row_index][col_index] == PLAYER_O)
                            thirdColor = "\033[94m\033[9m";
                        else if (board[row_index][col_index] == PLAYER_X)
                            thirdColor = "\033[91m\033[9m";

                        int num = i - (i - 1) / 4 - 1;

                        std::cout << "║  " << firstColor << num << colorEnd << "  ║  " << secondColor << num + 1 << colorEnd << "  ║  " << thirdColor << num + 2 << colorEnd << "  ║\n";

                    } else {
                        std::cout << "║     ║     ║     ║\n";
                    }
                } else if (j % 2 == 0) {
                    std::cout << " ║ ";
                } else {
                    int row_index = (i - 1) / 4;
                    int col_index = (j - 1) / 2;
                    if (board[row_index][col_index] != EMPTY) {
                        if (board[row_index][col_index] == PLAYER_O)
                            color = "\033[34m";
                        std::cout << color << board_map[board[row_index][col_index]][(i - 1) % 4] << colorEnd;
                    } else {
                        std::cout << "   ";
                    }
                }
            }
        }
    }
    /*
    0  1  2  3  4  5  6
    ╔═════╦═════╦═════╗ 0
    ║     ║     ║     ║ 1
    ║  1  ║  2  ║  3  ║ 2       0-0 0-1 0-2
    ║     ║     ║     ║ 3
    ╠═════╬═════╬═════╣ 4
    ║     ║     ║     ║ 5
    ║  4  ║  5  ║  6  ║ 6       1-0 1-1 1-2
    ║     ║     ║     ║ 7
    ╠═════╬═════╬═════╣ 8
    ║     ║     ║     ║ 9
    ║  7  ║  8  ║  9  ║ 10      2-0 2-1 2-2
    ║     ║     ║     ║ 11
    ╚═════╩═════╩═════╝ 12
    */
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
    std::vector<Move> moves;
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
