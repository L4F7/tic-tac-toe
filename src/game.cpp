#include <iostream>

#include "game.h"

const char EMPTY = ' ';
const char PLAYER_X = 'X';
const char PLAYER_O = 'O';

Game::Game() {
    this->interface = Interface();

}

Game::~Game() {}

Interface Game::getInterface() {
    return interface;
}

void Game::setInterface(Interface interface) {
    this->interface = interface;
}

Board Game::getBoard() {
    return board;
}

void Game::setBoard(Board board) {
    this->board = board;
}


void Game::start() {

    while (true){
        int option = interface.displayMenu();
        if (option == 1) this->playerVsPlayer();
        if (option == 2) {
            int mode = interface.displayBotMode();
            if (mode == 3) continue; // If the user goes back to the main menu
            this->playerVsBot(mode);
        };
        if (option == 3) interface.displayCredits();
        if (option == 4){
            interface.goodbye();
            break;
        } 
    }
}
bool Game::checkWinOrDraw(Board board) {

    if (board.checkWin(PLAYER_X)) {
        this->interface.displayBoard(board.getBoard());
        this->interface.displayWinMessage(PLAYER_X);
        return true;
    } else if (board.checkWin(PLAYER_O)) {
        this->interface.displayBoard(board.getBoard());
        this->interface.displayWinMessage(PLAYER_O);
        return true;
    } else if (board.isFull()) {
        this->interface.displayBoard(board.getBoard());
        this->interface.displayDrawMessage();
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
            this->interface.displayBoard(board.getBoard());
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
                this->interface.displayBoard(board.getBoard());
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

            this->interface.displayBoard(board.getBoard());

            auto start = std::chrono::high_resolution_clock::now();
            Move botMove = bot.getBestMove(board);
            auto stop = std::chrono::high_resolution_clock::now();

            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

            executionTimes.push_back(duration.count());

            board.placeMove(botMove.getRow(), botMove.getCol(), PLAYER_O);
            currentPlayer = PLAYER_X;
        }

        if (checkWinOrDraw(board))
            break;
    }

   this->interface.displayExecutionTimes(executionTimes);

}