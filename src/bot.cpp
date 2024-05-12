#include "bot.h"

// Constants
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

// Function to get the best move for the given player.
Move Bot::getBestMove(Board &board, char playerToSimulate) {

    // If the bot is set to use threading, use the threaded version.
    if (threaded) {
        return getBestMoveThreaded(board, playerToSimulate);
    } else { // Otherwise, use the non-threaded version.
        return getBestMoveNonThreaded(board, playerToSimulate);
    }
}

// Function to find the best move for the given player without using threading.
Move Bot::getBestMoveNonThreaded(Board &board, char playerToSimulate) {
    // Initialize the best score to a very low value.
    int bestScore = -1000;
    // Initialize the best move.
    Move bestMove;
    // Get all available moves on the current board.
    std::vector<Move> availableMoves = board.getAvailableMoves(); 

    try {
        // Iterate through each available move.
        for (const auto &move : availableMoves) {
            // Place the move on the board.
            board.placeMove(move.getRow(), move.getCol(), playerToSimulate);
            // Calculate the score for the current move using the Minimax algorithm.
            int score = minMax(board, false, playerToSimulate); 
            // Undo the move to revert the board back to its original state.
            board.placeMove(move.getRow(), move.getCol(), EMPTY); 
            // Update the best score and best move if the current move's score is better.
            if (score > bestScore) { 
                bestScore = score;
                bestMove = move;
            }
        }
    } catch (const std::exception &e) {
        // If an exception occurs during the calculation, return an invalid move.
        return {-1, -1};
    }

    // Return the best move found.
    return bestMove;
}

// Function to find the best move for the given player using threading if there are 
// enough available moves, otherwise fallbacks to non-threaded version.
Move Bot::getBestMoveThreaded(Board &board, char playerToSimulate) {
    // Get all available moves on the current board.
    std::vector<Move> availableMoves = board.getAvailableMoves();

    // If there are fewer than 5 available moves, use the non-threaded version for efficiency.
    if (availableMoves.size() < 5)
        return getBestMoveNonThreaded(board, playerToSimulate);

    // Initialize the best score to a very low value.
    int bestScore = -1000;
    // Initialize the best move.
    Move bestMove;
    // Vector to hold threads for parallel execution.
    std::vector<std::thread> threads;
    // Vector to hold scores for each move.
    std::vector<int> scores(availableMoves.size());

    try {
        // Start a thread for each available move to calculate scores concurrently.
        for (int i = 0; i < availableMoves.size(); i++) {
            threads.push_back(std::thread([this, &board, &scores, i, &availableMoves, playerToSimulate] {
                // Create a temporary board copy to simulate moves independently.
                Board tempBoard(board);
                // Simulate the move on the temporary board.
                tempBoard.placeMove(availableMoves[i].getRow(), availableMoves[i].getCol(), playerToSimulate);
                // Calculate the score for the move using the Minimax algorithm.
                scores[i] = minMax(tempBoard, false, playerToSimulate);
            }));
        }

        // Wait for all threads to finish execution.
        for (auto &thread : threads) {
            thread.join();
        }

        // Find the move with the highest score among all calculated scores.
        for (int i = 0; i < availableMoves.size(); i++) {
            if (scores[i] > bestScore) {
                bestScore = scores[i];
                bestMove = availableMoves[i];
            }
        }
    } catch (const std::exception &e) {
        // If an exception occurs during the calculation, return an invalid move.
        return {-1, -1};
    }

    // Return the best move found.
    return bestMove;
}

// Minimax algorithm implementation to determine the score of a board state for a given player.
int Bot::minMax(Board &board, bool isMaximizing, char playerToSimulate) {
    // Determine the opponent's symbol based on the current player.
    char opponent = (playerToSimulate == PLAYER_X) ? PLAYER_O : PLAYER_X;

    // Check if the current player has won.
    if (board.checkWin(playerToSimulate))
        return (playerToSimulate == PLAYER_O) ? 10 : -10;
    
    // Check if the opponent has won.
    if (board.checkWin(opponent))
        return (playerToSimulate == PLAYER_O) ? -10 : 10;
    
    // Check if the board is full, indicating a draw.
    if (board.isFull())
        return 0;

    // If it's the maximizing player's turn.
    if (isMaximizing) {
        int bestScore = -1000; // Initialize the best score to a very low value.
        std::vector<Move> availableMoves = board.getAvailableMoves();
        // Loop through each available move.
        for (const auto &move : availableMoves) {
            // Simulate the move for the current player.
            board.placeMove(move.getRow(), move.getCol(), playerToSimulate);
            // Recursively calculate the score for the next move.
            int score = minMax(board, false, playerToSimulate);
            // Undo the move to backtrack.
            board.placeMove(move.getRow(), move.getCol(), EMPTY);
            // Update the best score with the maximum value found.
            bestScore = std::max(bestScore, score);
        }
        // Return the best score for the maximizing player.
        return bestScore;
    } else { // If it's the minimizing player's turn.
        int bestScore = 1000; // Initialize the best score to a very high value.
        std::vector<Move> availableMoves = board.getAvailableMoves();
        // Loop through each available move.
        for (const auto &move : availableMoves) {
            // Simulate the move for the opponent.
            board.placeMove(move.getRow(), move.getCol(), opponent);
            // Recursively calculate the score for the next move.
            int score = minMax(board, true, playerToSimulate);
            // Undo the move to backtrack.
            board.placeMove(move.getRow(), move.getCol(), EMPTY);
            // Update the best score with the minimum value found.
            bestScore = std::min(bestScore, score);
        }
        // Return the best score for the minimizing player.
        return bestScore;
    }
}

/*


// Minmax algorithm using alpha-beta pruning
int Bot::minMax(Board &board, bool isMaximizing, char playerToSimulate, int alpha, int beta) {
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
            int score = minMax(board, false, playerToSimulate, alpha, beta);
            board.placeMove(move.getRow(), move.getCol(), EMPTY);
            bestScore = std::max(bestScore, score);
            alpha = std::max(alpha, bestScore);
            if (beta <= alpha)
                break; // Beta cutoff
        }
        return bestScore;
    } else {
        int bestScore = 1000;
        std::vector<Move> availableMoves = board.getAvailableMoves();
        for (const auto &move : availableMoves) {
            board.placeMove(move.getRow(), move.getCol(), opponent);
            int score = minMax(board, true, playerToSimulate, alpha, beta);
            board.placeMove(move.getRow(), move.getCol(), EMPTY);
            bestScore = std::min(bestScore, score);
            beta = std::min(beta, bestScore);
            if (beta <= alpha)
                break; // Alpha cutoff
        }
        return bestScore;
    }
}

int score = minMax(board, false, playerToSimulate, -1000, 1000);

*/