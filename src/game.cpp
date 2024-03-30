#include <iostream>

#include "game.h"

const char EMPTY = ' ';
const char PLAYER_X = 'X';
const char PLAYER_O = 'O';

bool Game::checkWinOrDraw(Board board) {

    if (board.checkWin(PLAYER_X)) {
        board.display();
        std::cout << "\n                 \033[91m╔══════════════╗\033[0m";
        std::cout << "\n                 \033[91m║Player X wins!║\033[0m";
        std::cout << "\n                 \033[91m╚══════════════╝\033[0m\n";
        return true;
    } else if (board.checkWin(PLAYER_O)) {
        board.display();

        std::cout << "\n                 \033[94m╔══════════════╗\033[0m";
        std::cout << "\n                 \033[94m║Player O wins!║\033[0m";
        std::cout << "\n                 \033[94m╚══════════════╝\033[0m\n";
        return true;
    } else if (board.isFull()) {
        board.display();
        std::cout << "\n                  ╔════════════╗";
        std::cout << "\n                  ║It's a draw!║";
        std::cout << "\n                  ╚════════════╝\n";
        return true;
    }
    return false;
}

void Game::playerVsPlayer() {
    Board board;

    char currentPlayer = PLAYER_X;

    while (true) {

        int position;

        while(true){
            board.display();
            std::cout << "\nPlayer " << currentPlayer << "'s turn. \nEnter position (1-9): ";
            std::cin >> position;

            if(std::cin.fail() || position < 1 || position > 9)  {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            } else {
                break;
            }
        }

        int row = (position - 1) / 3;
        int col = (position - 1) % 3;

        if (board.isEmpty(row, col)) {
            board.placeMove(row, col, currentPlayer);
            currentPlayer = (currentPlayer == PLAYER_X) ? PLAYER_O : PLAYER_X;
        } else {
            std::cout << "\nInvalid move! Press ENTER to try again...\n";
            std::cin.ignore().get();
            continue;
        }

        if (checkWinOrDraw(board))
            break;
    }

    std::cout << "\nPress ENTER to go back to the main menu...";
    std::cin.ignore().get();
}

void Game::playerVsBot(int mode) {
    Board board;
    Bot bot;
    if (mode == 2)
        bot.setMode(1);

    char currentPlayer = PLAYER_X;
    std::vector<int> executionTimes;

    while (true) {

        if (currentPlayer == PLAYER_X) {
            int position;
        
            while(true){
                board.display();
                std::cout << "\nPlayer " << currentPlayer << "'s turn. \nEnter position (1-9): ";
                std::cin >> position;

                if(std::cin.fail() || position < 1 || position > 9)  {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                } else {
                    break;
                }
            }

            int row = (position - 1) / 3;
            int col = (position - 1) % 3;

            if (board.isEmpty(row, col)) {
                board.placeMove(row, col, PLAYER_X);
                currentPlayer = PLAYER_O;
            } else {
                std::cout << "\nInvalid move! Press ENTER to try again...\n";
                std::cin.ignore().get();
                continue;
            }
        } else {

            board.display();

            // std::cout << "\n Bot's turn...\n";
            // std::this_thread::sleep_for(std::chrono::milliseconds(1000));

            auto start = std::chrono::high_resolution_clock::now();
            Move botMove = bot.getBestMove(board);
            auto stop = std::chrono::high_resolution_clock::now();

            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

            executionTimes.push_back(duration.count());

            board.placeMove(botMove.row, botMove.col, PLAYER_O);
            currentPlayer = PLAYER_X;
        }

        if (checkWinOrDraw(board))
            break;
    }

    //  ARREGLAR CON STD::LEFT Y STD::SETW

    std::cout << "\n\033[92m          ╔════════════════════════════╗";
    std::cout << "\n          ║Bot movement execution times║";
    std::cout << "\n          ╠════════════════════════════╣\n";
    for (int i = 0; i < executionTimes.size(); i++) {
        std::cout << "          ║" << std::right << std::setw(10) << executionTimes[i] << std::left << std::setw(18) << " microseconds" << "║\n";
    }
    std::cout << "          ╚════════════════════════════╝\033[0m\n";
    std::cout << "\n Press ENTER to go back to the main menu...";
    std::cin.ignore().get();
}
/*
    ╚═════╩═════╩═════╝    ╚═════╩═════╩═════╝
          ╔════════════════════════════╗
*/