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
    initNcurses();   // Initialize ncurses
    runMenu();       // Run the menu
    endNcurses();    // End ncurses
    system("clear"); // Clear the terminal
}

void Game::initNcurses() {

    setlocale(LC_ALL, "");

    initscr();            // Initialize ncurse
    raw();                // Disable line buffering
    keypad(stdscr, TRUE); // Enable keypad for arrow keys

    use_default_colors();          // Use default colors
    start_color();                 // Start color mode
    init_pair(1, COLOR_RED, -1);   // Define color pair 1 (red)
    init_pair(2, COLOR_BLUE, -1);  // Define color pair 2 (blue)
    init_pair(3, COLOR_GREEN, -1); // Define color pair 2 (green)
}

void Game::endNcurses() {
    refresh(); // Refresh the screen
    endwin();  // End ncurses
}

void Game::runMenu() {

    while (true) {

        attron(COLOR_PAIR(3)); // Set color pair 3 (green)
        int option = interface.menu();
        attroff(COLOR_PAIR(3)); // Reset color pair

        if (option == 1) {
            playerVsPlayer();
            interface.displayGetBackToMenu();
        }

        if (option == 2) {
            runBotMenu();
        }

        if (option == 3) {
            attron(COLOR_PAIR(3));    // Set color pair 3 (green)
            interface.displayCredits();
            interface.displayGetBackToMenu();
            attroff(COLOR_PAIR(3)); // Reset color pair
        }

        if (option == 4) {
            fileManager.clearExecutionTimes("../executionTimes.csv");
            break;
        }
    }
}

void Game::runBotMenu() {

    while (true) {

        attron(COLOR_PAIR(3)); // Set color pair 3 (green)
        int botMenuChoice = interface.botMenu();
        attroff(COLOR_PAIR(3)); // Reset color pair

        if (botMenuChoice == 1) {
            playerVsBot(0, false); // Non-threaded
        }

        if (botMenuChoice == 2) {
            playerVsBot(1, false); // Threaded
        }

        if (botMenuChoice == 3) {
            runSimulateGamesMenu();
        }

        if (botMenuChoice == 4) {
            break;
        }
    }
}

void Game::runSimulateGamesMenu() {

    attron(COLOR_PAIR(3));    // Set color pair 3 (green)
    int numberOfGames = interface.simulateGamesMenu(); // Get number of games to simulate
    attroff(COLOR_PAIR(3)); // Reset color pair

    if(numberOfGames == 0) {
        return;
    }

    attron(COLOR_PAIR(3));    // Set color pair 3 (green)
    interface.displayLoading();
    attroff(COLOR_PAIR(3)); // Reset color pair

    simulateGames(numberOfGames, 0);
    simulateGames(numberOfGames, 1);

    flushinp(); // Flush input buffer

    attron(COLOR_PAIR(3));    // Set color pair 3 (green)
    interface.displayStats(); // Display stats
    interface.displayGetBackToMenu();
    attroff(COLOR_PAIR(3)); // Reset color pair
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

void Game::playerVsBot(int mode, bool simulated) {
    Board board;
    Bot bot;
    if (mode == 1)
        bot.setMode(1);

    char currentPlayer = PLAYER_X;
    std::vector<std::pair<int, int>> executionTimes;

    while (true) {

        if (currentPlayer == PLAYER_X) {
            int position;
            if (simulated) {
                position = bot.getBestMove(board).getRow() * 3 + bot.getBestMove(board).getCol() + 1;
            } else {
                position = interface.playerTurn(currentPlayer, board);
            }

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

            executionTimes.push_back(std::make_pair(mode, duration.count()));

            board.placeMove(botMove.getRow(), botMove.getCol(), PLAYER_O);
            currentPlayer = PLAYER_X;
        }

        if (checkWinOrDraw(board))
            break;
    }

    interface.displayExecutionTimes(executionTimes);
    saveExecutionTimes(executionTimes);
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

void Game::saveExecutionTimes(std::vector<std::pair<int, int>> executionTimes) {
    FileManager fileManager;
    std::vector<std::string> lines;
    for (const auto &[mode, time] : executionTimes) {
        std::string line = std::to_string(mode) + "," + std::to_string(time);
        lines.push_back(line);
    }
    fileManager.writeExecutionTimes("../executionTimes.csv", lines);
}

void Game::simulateGames(int games, int mode) {
    for (int i = 0; i < games; i++) {
        playerVsBot(mode, true);
    }
}