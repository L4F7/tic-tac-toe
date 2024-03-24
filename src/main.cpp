#include <iostream>
#include <chrono>
#include <vector>
#include "board.h"
#include "bot.h"

const char EMPTY = ' ';
const char PLAYER_X = 'X';
const char PLAYER_O = 'O';


int main() {
    Board board;
    Bot bot;
    std::vector <int> executionTimes;

    char currentPlayer = PLAYER_X;

    std::cout << "\n      Tic Tac Toe Game" << std::endl;

    while (true) {
        board.display();

        if (currentPlayer == PLAYER_X) {
            int position;
            std::cout << "\nPlayer X's turn. Enter position (1-9): ";
            std::cin >> position;

            int row = (position - 1) / 3;
            int col = (position - 1) % 3;

            if (position < 1 || position > 9) {
                std::cout << "\nInvalid position! Try again." << std::endl;
                continue;
            }

            if (board.isEmpty(row, col)) {
                board.placeMove(row, col, PLAYER_X);
                currentPlayer = PLAYER_O;
            } else {
                std::cout << "\nInvalid move! Try again." << std::endl;
                continue;
            }
        } else {
            std::cout << "\nBot's turn..." << std::endl;

            auto start = std::chrono::high_resolution_clock::now();
            Move botMove = bot.getBestMove(board);
            auto stop = std::chrono::high_resolution_clock::now();

            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
            executionTimes.push_back(duration.count());

            // auto start = high_resolution_clock::now();
            // Move botMove = bot.getBestMoveThreaded(board);
            // auto stop = high_resolution_clock::now();

            // auto duration = duration_cast<nanoseconds>(stop - start);
            // executionTimes.push_back(duration.count());

            board.placeMove(botMove.row, botMove.col, PLAYER_O);
            currentPlayer = PLAYER_X;
        }

        if (board.checkWin(PLAYER_X)) {
            board.display();
            std::cout << "Player X wins!" << std::endl;
            break;
        } else if (board.checkWin(PLAYER_O)) {
            board.display();
            std::cout << "Player O wins!" << std::endl;
            break;
        } else if (board.isFull()) {
            board.display();
            std::cout << "It's a draw!" << std::endl;
            break;
        }
    }

    std::cout << "\nExecution times: \n" << std::endl;
    for(auto time: executionTimes) {
        std::cout << "Execution time: " << time << " nanoseconds" << std::endl;
    }

    return 0;
}