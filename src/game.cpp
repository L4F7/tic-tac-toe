#include <iostream>

#include "game.h"

const char EMPTY = ' ';
const char PLAYER_X = 'X';
const char PLAYER_O = 'O';

bool Game::checkWinOrDraw(Board board){
    if (board.checkWin(PLAYER_X)) {
        board.display();
        std::cout << std::endl << "       ¡Player X wins!" << std::endl;
        return true;
    } else if (board.checkWin(PLAYER_O)) {
        board.display();
        std::cout << std::endl << "       ¡Player O wins!" << std::endl;
        return true;
    } else if (board.isFull()) {
        board.display();
        std::cout << std::endl << "        ¡It's a draw!" << std::endl;
        return true;
    }

    return false;
}

void Game::playerVsPlayer() {
    Board board;

    char currentPlayer = PLAYER_X;

    while (true) {
        board.display();

        int position;
        std::cout << std::endl << "Player " << currentPlayer << "'s turn. Enter position (1-9): ";
        std::cin >> position;

        int row = (position - 1) / 3;
        int col = (position - 1) % 3;

        if (position < 1 || position > 9) {
            std::cout << std::endl  << "Invalid position! Try again." << std::endl;
            continue;
        }

        if (board.isEmpty(row, col)) {
            board.placeMove(row, col, currentPlayer);
            currentPlayer = (currentPlayer == PLAYER_X) ? PLAYER_O : PLAYER_X;
        } else {
            std::cout << std::endl  << "Invalid move! Try again." << std::endl;
            continue;
        }

        if(checkWinOrDraw(board)) break;
        
    }

    std::cout << std::endl << "Press ENTER to go back to the main menu...";
    std::cin.ignore().get();

}

void Game::playerVsBot(int mode) {
    Board board;
    Bot bot;
    if (mode == 2) bot.setMode(1);

    char currentPlayer = PLAYER_X;
    std::vector < int > executionTimes;

    while (true) {
        system("clear");
        board.display();

        if (currentPlayer == PLAYER_X) {
            int position;
            std::cout << std::endl  << "Player X's turn. Enter position (1-9): ";
            std::cin >> position;

            int row = (position - 1) / 3;
            int col = (position - 1) % 3;

            if (position < 1 || position > 9) {
                std::cout << std::endl  << "Invalid position! Try again." << std::endl;
                continue;
            }

            if (board.isEmpty(row, col)) {
                board.placeMove(row, col, PLAYER_X);
                currentPlayer = PLAYER_O;
            } else {
                std::cout << std::endl  << "Invalid move! Try again." << std::endl;
                continue;
            }
        } else {
            std::cout << "\nBot's turn..." << std::endl;

            auto start = std::chrono::high_resolution_clock::now();
            Move botMove = bot.getBestMove(board);
            auto stop = std::chrono::high_resolution_clock::now();

            auto duration = std::chrono::duration_cast < std::chrono::microseconds > (stop - start);

            executionTimes.push_back(duration.count());

            board.placeMove(botMove.row, botMove.col, PLAYER_O);
            currentPlayer = PLAYER_X;
        }

        if(checkWinOrDraw(board)) break;
    }

    std::cout << std::endl << "Execution times: " << std::endl  << std::endl;
    for (auto time: executionTimes) {
        std::cout << "Execution time: " << time << " microseconds" << std::endl;
    }

    std::cout << std::endl << "Press ENTER to go back to the main menu...";
    std::cin.ignore().get();

}