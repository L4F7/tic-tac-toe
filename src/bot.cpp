#include "bot.h"

// Constants for the game symbols
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

/**
 * @brief Finds the best move for a given player using the Minimax algorithm, with or without threads.
 */
Move Bot::getBestMove(Board &board, char playerToSimulate) {
    // Check if multithreading is enabled
    if (threaded) {
        // If threaded, use the threaded version of the function to find the best move
        return getBestMoveThreaded(board, playerToSimulate);
    } else {
        // If not threaded, use the non-threaded version of the function to find the best move
        return getBestMoveNonThreaded(board, playerToSimulate);
    }
}

/**
 * @brief Finds the best move for a given player without using threads.
 */
Move Bot::getBestMoveNonThreaded(Board &board, char playerToSimulate) {
    int bestScore = -1000; // Initialize the best score to a very low value
    Move bestMove; // Initialize the best move
    std::vector<Move> availableMoves = board.getAvailableMoves(); // Get all available moves on the board

    try {
        // Iterate through each available move
        for (const auto &move : availableMoves) {
            // Place the move on the board
            board.placeMove(move.getRow(), move.getCol(), playerToSimulate);
            // Calculate the score using the Minimax algorithm
            int score = minMax(board, false, playerToSimulate); 
            // Undo the move
            board.placeMove(move.getRow(), move.getCol(), EMPTY); 

            // If the current move yields a higher score than the previous best, update the best score and move
            if (score > bestScore) { 
                bestScore = score;
                bestMove = move;
            }
        }
    } catch (const std::exception &e) {
        // In case of an exception, return an invalid move
        return {-1, -1};
    }

    // Return the best move found
    return bestMove;
}

/**
 * @brief Finds the best move for a given player using threads.
 */
Move Bot::getBestMoveThreaded(Board &board, char playerToSimulate) {
    std::vector<Move> availableMoves = board.getAvailableMoves(); // Get all available moves on the board

    // If the number of available moves is less than 5, fall back to non-threaded approach
    if (availableMoves.size() < 5)
        return getBestMoveNonThreaded(board, playerToSimulate);

    int bestScore = -1000; // Initialize the best score to a very low value
    Move bestMove; // Initialize the best move
    std::vector<std::thread> threads; // Container for threads
    std::vector<int> scores(availableMoves.size()); // Container for scores corresponding to each move

    try {
        // Create threads to evaluate each move concurrently
        for (int i = 0; i < availableMoves.size(); i++) {
            threads.push_back(std::thread([this, &board, &scores, i, &availableMoves, playerToSimulate] {
                Board tempBoard(board);
                tempBoard.placeMove(availableMoves[i].getRow(), availableMoves[i].getCol(), playerToSimulate);
                scores[i] = minMax(tempBoard, false, playerToSimulate); // Calculate the score for the move
            }));
        }

        // Wait for all threads to finish
        for (auto &thread : threads) {
            thread.join();
        }

        // Find the move with the highest score
        for (int i = 0; i < availableMoves.size(); i++) {
            if (scores[i] > bestScore) {
                bestScore = scores[i];
                bestMove = availableMoves[i];
            }
        }
    } catch (const std::exception &e) {
        // In case of an exception, return an invalid move
        return {-1, -1};
    }

    // Return the best move found
    return bestMove;
}

/**
 * @brief Implements the Minimax algorithm to determine the score of a given game state.
 */
int Bot::minMax(Board &board, bool isMaximizing, char playerToSimulate) {
    // Get the opponent's symbol
    char opponent = (playerToSimulate == PLAYER_X) ? PLAYER_O : PLAYER_X;

    // If the current player wins, return a high score; if the opponent wins, return a low score
    if (board.checkWin(playerToSimulate))
        return (playerToSimulate == PLAYER_O) ? 10 : -10;
    
    if (board.checkWin(opponent))
        return (playerToSimulate == PLAYER_O) ? -10 : 10;
    
    // If the board is full and no one wins, return a neutral score
    if (board.isFull())
        return 0;

    // If the current player is maximizing
    if (isMaximizing) {
        int bestScore = -1000; // Initialize the best score to a very low value
        std::vector<Move> availableMoves = board.getAvailableMoves(); // Get all available moves for the current player
        // Evaluate each available move recursively
        for (const auto &move : availableMoves) {
            board.placeMove(move.getRow(), move.getCol(), playerToSimulate); // Place the move on the board
            int score = minMax(board, false, playerToSimulate); // Recursively calculate the score
            board.placeMove(move.getRow(), move.getCol(), EMPTY); // Undo the move
            bestScore = std::max(bestScore, score); // Update the best score
        }
        return bestScore; // Return the best score found
    } 
    // If the current player is minimizing
    else {
        int bestScore = 1000; // Initialize the best score to a very high value
        std::vector<Move> availableMoves = board.getAvailableMoves(); // Get all available moves for the opponent
        // Evaluate each available move recursively
        for (const auto &move : availableMoves) {
            board.placeMove(move.getRow(), move.getCol(), opponent); // Place the move on the board
            int score = minMax(board, true, playerToSimulate); // Recursively calculate the score
            board.placeMove(move.getRow(), move.getCol(), EMPTY); // Undo the move
            bestScore = std::min(bestScore, score); // Update the best score
        }
        return bestScore; // Return the best score found
    }
}
