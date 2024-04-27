#include "game.h"

const char EMPTY = ' ';
const char PLAYER_X = 'X';
const char PLAYER_O = 'O';

Game::Game() {
    interface = Interface();
}

Game::~Game() {}

Interface Game::getInterface() {
    return interface;
}

void Game::setInterface(Interface interface) {
    interface = interface;
}

void Game::start() {
    
    setlocale(LC_ALL, "");

    initscr(); // Initialize ncurse
    raw(); // Disable line buffering
    keypad(stdscr, TRUE); // Enable keypad for arrow keys

    use_default_colors(); // Use default colors
    start_color(); // Start color mode
    init_pair(1, COLOR_RED, -1); // Define color pair 1 (red)
    init_pair(2, COLOR_BLUE, -1); // Define color pair 2 (blue)
    init_pair(3, COLOR_GREEN, -1); // Define color pair 2 (green)

    while (true) {
        int option = interface.menu();

        if (option == 1) {
            playerVsPlayer();
            interface.displayGetBackToMenu();
        }

        if (option == 2) {
            int mode = interface.botMode();
            if (mode == 3)
                continue; // If the user goes back to the main menu
            playerVsBot(mode);
            interface.displayGetBackToMenu();
        }

        if (option == 3) {
            interface.displayCredits();
            interface.displayGetBackToMenu();
        }

        if (option == 4) {
            interface.displayGoodbye();
            break;
        }
    }
    
    refresh(); // Refresh the screen
    endwin(); // End ncurses

    system("clear"); // Clear the terminal

}
bool Game::checkWinOrDraw(Board board) {

    if (board.checkWin(PLAYER_X)) {
        clear();
        interface.displayBoard(board.getBoard());
        interface.displayWinMessage(PLAYER_X);
        return true;
    } else if (board.checkWin(PLAYER_O)) {
        clear();
        interface.displayBoard(board.getBoard());
        interface.displayWinMessage(PLAYER_O);
        return true;
    } else if (board.isFull()) {
        clear();
        interface.displayBoard(board.getBoard());
        interface.displayDrawMessage();
        return true;
    }
    return false;
}

void Game::playerVsPlayer() {
    Board board;

    char currentPlayer = PLAYER_X;

    while (true) {

        int position = interface.playerTurn(currentPlayer, board);

        refresh();

        int row = (position - 1) / 3;
        int col = (position - 1) % 3;

        if (board.isEmpty(row, col)) {
            board.placeMove(row, col, currentPlayer);
            currentPlayer = (currentPlayer == PLAYER_X) ? PLAYER_O : PLAYER_X;
        } else {
            interface.displayInvalidMove();
            continue;
        }

        if (checkWinOrDraw(board))
            break;
    }

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
            int position = interface.playerTurn(currentPlayer, board);

            int row = (position - 1) / 3;
            int col = (position - 1) % 3;

            if (board.isEmpty(row, col)) {
                board.placeMove(row, col, PLAYER_X);
                currentPlayer = PLAYER_O;
            } else {
                interface.displayInvalidMove();
                continue;
            }
        } else {

            clear();

            interface.displayBoard(board.getBoard());

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

    interface.displayExecutionTimes(executionTimes);

}