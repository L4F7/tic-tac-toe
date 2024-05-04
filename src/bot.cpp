#include "bot.h"

const char EMPTY = ' ';
const char PLAYER_X = 'X';
const char PLAYER_O = 'O';

Bot::Bot() {
    threaded = false;
}

Bot::~Bot() {
}

void Bot::setThreaded(bool threaded) {
    this->threaded = threaded;
}

int Bot::getThreaded() {
    return threaded;
}

Move Bot::getBestMove(Board &board, char playerToSimulate) {
    if (threaded) {
        return getBestMoveThreaded(board, playerToSimulate);
    } else {
        return getBestMoveNonThreaded(board, playerToSimulate);
    }
}

Move Bot::getBestMoveNonThreaded(Board &board, char playerToSimulate) {
    int bestScore = -1000;
    Move bestMove;
    std::vector<Move> availableMoves = board.getAvailableMoves();
    for (const auto &move : availableMoves) {
        board.placeMove(move.getRow(), move.getCol(), playerToSimulate);
        int score = minMax(board, false, playerToSimulate);
        board.placeMove(move.getRow(), move.getCol(), EMPTY);
        if (score > bestScore) {
            bestScore = score;
            bestMove = move;
        }
    }
    return bestMove;
}

Move Bot::getBestMoveThreaded(Board &board, char playerToSimulate) {
    std::vector<Move> availableMoves = board.getAvailableMoves();

    if (availableMoves.size() < 5)
        return getBestMoveNonThreaded(board, playerToSimulate);

    int bestScore = -1000;
    Move bestMove;
    std::vector<std::thread> threads;
    std::vector<int> scores(availableMoves.size());

    for (int i = 0; i < availableMoves.size(); i++) {
        threads.push_back(std::thread([this, &board, &scores, i, &availableMoves, playerToSimulate] {
            Board tempBoard(board);
            tempBoard.placeMove(availableMoves[i].getRow(), availableMoves[i].getCol(), playerToSimulate);
            scores[i] = minMax(tempBoard, false, playerToSimulate);
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


int Bot::minMax(Board &board, bool isMaximizing, char playerToSimulate) {
    char opponent = (playerToSimulate == PLAYER_X) ? PLAYER_O : PLAYER_X;

    if (board.checkWin(playerToSimulate))
        return (playerToSimulate == PLAYER_O) ? 10 : -10;
    if (board.checkWin(opponent))
        return (playerToSimulate == PLAYER_O) ? -10 : 10;
    if (board.isFull())
        return 0;

    if (isMaximizing) {
        int bestScore = -1000;
        std::vector<Move> availableMoves = board.getAvailableMoves();
        for (const auto &move : availableMoves) {
            board.placeMove(move.getRow(), move.getCol(), playerToSimulate);
            int score = minMax(board, false, playerToSimulate);
            board.placeMove(move.getRow(), move.getCol(), EMPTY);
            bestScore = std::max(bestScore, score);
        }
        return bestScore;
    } else {
        int bestScore = 1000;
        std::vector<Move> availableMoves = board.getAvailableMoves();
        for (const auto &move : availableMoves) {
            board.placeMove(move.getRow(), move.getCol(), opponent);
            int score = minMax(board, true, playerToSimulate);
            board.placeMove(move.getRow(), move.getCol(), EMPTY);
            bestScore = std::min(bestScore, score);
        }
        return bestScore;
    }
}

