#include <vector>
#include <algorithm>
#include <iostream>
#include <thread>

#include "bot.h"
#include "board.h"
#include "move.h"

const char EMPTY = ' ';
const char PLAYER_X = 'X';
const char PLAYER_O = 'O';

void Bot::setMode(int mode) {
    this->mode = mode;
}

int Bot::getMode() {
    return mode;
}

Move Bot::getBestMove(Board & board) {
    if (mode) {
        std::cout << "Threaded" << std::endl;
        return getBestMoveThreaded(board);
    } else {
        std::cout << "Non-mode" << std::endl;
        return getBestMoveNonThreaded(board);
    }
}

Move Bot::getBestMoveNonThreaded(Board & board) {
    int bestScore = -1000;
    Move bestMove;
    std::vector <Move> availableMoves = board.getAvailableMoves();
    for (const auto & move: availableMoves) {
        board.placeMove(move.row, move.col, PLAYER_O);
        int score = minMax(board, false);
        board.placeMove(move.row, move.col, EMPTY);
        if (score > bestScore) {
            bestScore = score;
            bestMove = move;
        }
    }
    return bestMove;
}

Move Bot::getBestMoveThreaded(Board & board) {
    std::vector<Move> availableMoves = board.getAvailableMoves();

    if (availableMoves.size() < 5) return getBestMoveNonThreaded(board);

    int bestScore = -1000;
    Move bestMove;
    std::vector<std::thread> threads;

    for (const auto & move : availableMoves) {
        threads.emplace_back([&]() {
            Board tempBoard(board); // Create a temporary board for each thread
            tempBoard.placeMove(move.row, move.col, PLAYER_O);
            int score = minMax(tempBoard, false);
            if (score > bestScore) {
                bestScore = score;
                bestMove = move;
            }
        });
    }

    for (auto & thread : threads) {
        thread.join(); // Wait for all threads to finish
    }

    return bestMove;
}

int Bot::minMax(Board & board, bool isMaximizing) {
    if (board.checkWin(PLAYER_X)) return -10;
    if (board.checkWin(PLAYER_O)) return 10;
    if (board.isFull()) return 0;

    if (isMaximizing) {
        int bestScore = -1000;
        std::vector <Move> availableMoves = board.getAvailableMoves();
        for (const auto & move: availableMoves) {
            board.placeMove(move.row, move.col, PLAYER_O);
            int score = minMax(board, false);
            board.placeMove(move.row, move.col, EMPTY);
            bestScore = std::max(bestScore, score);
        }
        return bestScore;
    } else {
        int bestScore = 1000;
        std::vector <Move> availableMoves = board.getAvailableMoves();
        for (const auto & move: availableMoves) {
            board.placeMove(move.row, move.col, PLAYER_X);
            int score = minMax(board, true);
            board.placeMove(move.row, move.col, EMPTY);
            bestScore = std::min(bestScore, score);
        }
        return bestScore;
    }
}
