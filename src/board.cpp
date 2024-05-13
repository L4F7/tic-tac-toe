#include "board.h"

// Constants for the game symbols
const char EMPTY = ' ';
const char PLAYER_X = 'X';
const char PLAYER_O = 'O';

Board::Board() {
    board = std::vector<std::vector<char>>(3, std::vector<char>(3, EMPTY));
}

Board::Board(std::vector<std::vector<char>> board) {
    this->board = board;
}

Board::~Board() {}

std::vector<std::vector<char>> Board::getBoard() {
    return board;
}

void Board::setBoard(std::vector<std::vector<char>> board) {
    this->board = board;
}

/**
 * @brief Checks if the game board is full (no empty cells remaining).
 */
bool Board::isFull() {
    // Iterate through each cell to check if any is empty
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] == EMPTY)
                return false;
        }
    }
    return true;
}

/**
 * @brief Checks if the specified cell is empty.
 */
bool Board::isEmpty(int row, int col) {
    return board[row][col] == EMPTY;
}

/**
 * @brief Places a move (player symbol) on the specified cell.
 */
void Board::placeMove(int row, int col, char playerSymbol) {
    board[row][col] = playerSymbol;
}

/**
 * @brief Checks if the specified player has won the game.
 */
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

/**
 * @brief Gets a list of available moves (empty cells) on the board.
 */
std::vector<Move> Board::getAvailableMoves() {
    std::vector<Move> moves;
    // Iterate through each cell to find available moves
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] == EMPTY) {
                moves.push_back({i, j});
            }
        }
    }
    return moves;
}

/**
 * @brief Gets the position of the first available move (empty cell) on the board, otherwise returns {-1, -1} if out of bounds.
 */
std::vector<int> Board::getFirstAvailableMove() {
    // Iterate through each cell to find the first available move
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] == EMPTY) {
                return {i, j};
            }
        }
    }
    return {-1, -1}; // No move available
}

/**
 * @brief Gets the position of the cell above the specified position, otherwise returns {-1, -1} if out of bounds.
 */
std::vector<int> Board::getMoveUp(std::vector<int> position) {
    int row = position[0];
    int col = position[1];
    if (row - 1 >= 0) {
        return {row - 1, col};
    }
    return {-1, -1}; // Out of bounds
}

/**
 * @brief Gets the position of the cell below the specified position, otherwise returns {-1, -1} if out of bounds.
 */
std::vector<int> Board::getMoveDown(std::vector<int> position) {
    int row = position[0];
    int col = position[1];
    if (row + 1 < 3) {
        return {row + 1, col};
    }
    return {-1, -1}; // Out of bounds
}

/**
 * @brief Gets the position of the cell to the left of the specified position, otherwise returns {-1, -1} if out of bounds.
 */
std::vector<int> Board::getMoveLeft(std::vector<int> position) {
    int row = position[0];
    int col = position[1];
    if (col - 1 >= 0) {
        return {row, col - 1};
    }
    return {-1, -1}; // Out of bounds
}

/**
 * @brief Gets the position of the cell to the right of the specified position, otherwise returns {-1, -1} if out of bounds.
 */
std::vector<int> Board::getMoveRight(std::vector<int> position) {
    int row = position[0];
    int col = position[1];
    if (col + 1 < 3) {
        return {row, col + 1};
    }
    return {-1, -1}; // Out of bounds
}

/**
 * @brief Clears the game board by setting all cells to EMPTY.
 */
void Board::clearBoard() {
    // Set all cells to EMPTY
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            board[i][j] = EMPTY;
        }
    }
}

