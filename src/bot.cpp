#include <algorithm>
#include <iostream>
#include <thread>
#include <vector>

#include "board.h"
#include "bot.h"
#include "move.h"

const char EMPTY = ' ';
const char PLAYER_X = 'X';
const char PLAYER_O = 'O';

Bot::Bot() {
    mode = 0;
}

Bot::~Bot() {
}

void Bot::setMode(int mode) {
    this->mode = mode;
}

int Bot::getMode() {
    return mode;
}

Move Bot::getBestMove(Board &board) {
    if (mode) {
        return getBestMoveThreaded(board);
    } else {
        return getBestMoveNonThreaded(board);
    }
}

Move Bot::getBestMoveNonThreaded(Board &board) {
    int bestScore = -1000;
    Move bestMove;
    std::vector<Move> availableMoves = board.getAvailableMoves();
    for (const auto &move : availableMoves) {
        board.placeMove(move.getRow(), move.getCol(), PLAYER_O);
        int score = minMax(board, false);
        board.placeMove(move.getRow(), move.getCol(), EMPTY);
        if (score > bestScore) {
            bestScore = score;
            bestMove = move;
        }
    }
    return bestMove;
}

Move Bot::getBestMoveThreaded(Board &board) {
    std::vector<Move> availableMoves = board.getAvailableMoves();

    if (availableMoves.size() < 5)
        return getBestMoveNonThreaded(board);

    int bestScore = -1000;
    Move bestMove;
    std::vector<std::thread> threads;
    std::vector<int> scores(availableMoves.size());

    for (int i = 0; i < availableMoves.size(); i++) {
        threads.push_back(std::thread([this, &board, &scores, i, &availableMoves] {
            Board tempBoard(board);
            tempBoard.placeMove(availableMoves[i].getRow(), availableMoves[i].getCol(), PLAYER_O);
            scores[i] = minMax(tempBoard, false);
        }));
    }

    for (auto &thread : threads) {
        thread.join();
    }

    for (int i = 0; i < availableMoves.size(); i++) {
        if (scores[i] > bestScore) {
            bestScore = scores[i];
            bestMove = availableMoves[i];
        }
    }

    return bestMove;
}

int Bot::minMax(Board &board, bool isMaximizing) {
    if (board.checkWin(PLAYER_X))
        return -10;
    if (board.checkWin(PLAYER_O))
        return 10;
    if (board.isFull())
        return 0;

    if (isMaximizing) {
        int bestScore = -1000;
        std::vector<Move> availableMoves = board.getAvailableMoves();
        for (const auto &move : availableMoves) {
            board.placeMove(move.getRow(), move.getCol(), PLAYER_O);
            int score = minMax(board, false);
            board.placeMove(move.getRow(), move.getCol(), EMPTY);
            bestScore = std::max(bestScore, score);
        }
        return bestScore;
    } else {
        int bestScore = 1000;
        std::vector<Move> availableMoves = board.getAvailableMoves();
        for (const auto &move : availableMoves) {
            board.placeMove(move.getRow(), move.getCol(), PLAYER_X);
            int score = minMax(board, true);
            board.placeMove(move.getRow(), move.getCol(), EMPTY);
            bestScore = std::min(bestScore, score);
        }
        return bestScore;
    }
}
