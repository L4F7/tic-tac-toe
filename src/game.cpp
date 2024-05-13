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

/**
 * @brief Starts the game
 */
void Game::start() {
    initNcurses();
    runMainMenu();
    endNcurses();
    system("clear");
}

/**
 * @brief Initializes ncurses
 */
void Game::initNcurses() {

    setlocale(LC_ALL, "");

    initscr();
    raw();
    keypad(stdscr, TRUE);

    use_default_colors();
    start_color();

    // -1 is the terminal default text or background color

    init_pair(1, COLOR_GREEN, -1);
    init_pair(2, COLOR_RED, -1);
    init_pair(3, COLOR_BLUE, -1);
}

/**
 * @brief Ends ncurses
 */
void Game::endNcurses() {
    refresh();
    endwin();
}

/**
 * @brief Runs the main menu
 */
void Game::runMainMenu() {

    std::vector<std::string> options = {"Player vs Player", "Player vs Bot", "Credits", "Exit"};
    std::string menuMessage = "Use the arrow keys to navigate the menu";

    while (true) {

        int option = interface.menu(options, menuMessage);

        if (option == 0) {
            playerVsPlayer();
        } else if (option == 1) {
            runBotMenu();
        } else if (option == 2) {
            interface.displayCredits();
        } else if (option == 3) {
            fileManager.clearExecutionTimes("../executionTimes.csv");
            break;
        }
    }
}

/**
 * @brief Runs the bot menu
 */
void Game::runBotMenu() {

    std::vector<std::string> options = {"Non-threaded", "Threaded", "Simulate games", "Back"};
    std::string menuMessage = "Use the arrow keys to navigate the menu";

    while (true) {

        int option = interface.menu(options, menuMessage);

        if (option == 0) {
            playerVsBot(0); // Non-threaded
            interface.displayGetBackToMenu();
        }else if (option == 1) {
            playerVsBot(1); // Threaded
            interface.displayGetBackToMenu();
        } else if (option == 2) {
            runSimulateGamesMenu();
        } else if (option == 3) {
            break;
        }
    }
}

/**
 * @brief Runs the simulate games menu
 */
void Game::runSimulateGamesMenu() {

    // Map to get the number of games from the option selected
    std::map<int, int> optionsMap = {
        {0, 5},
        {1, 10},
        {2, 15},
        {3, 0}
    };

    std::vector<std::string> options = {"5 games", "10 games", "15 games", "Back"};
    std::string menuMessage = "Use the arrow keys to navigate the menu";

    int numberOfGames = optionsMap[interface.menu(options, menuMessage)];

    if(numberOfGames == 0) {
        return;
    }

    interface.displaySimulating();

    refresh();

    simulateGames(numberOfGames, 0); // Non-threaded
    simulateGames(numberOfGames, 1); // Threaded

    flushinp(); // Flush input buffer

    interface.displayStats(); // Display stats
}

/**
 * @brief Player vs player game
 */
void Game::playerVsPlayer() {
    Board board;

    char currentPlayer = PLAYER_X;

    while (true) {

        Move position = interface.playingBoard(currentPlayer, board);

        refresh();

        int row = position.getRow();
        int col = position.getCol();

        if (board.isEmpty(row, col)) { 
            board.placeMove(row, col, currentPlayer);
            currentPlayer = (currentPlayer == PLAYER_X) ? PLAYER_O : PLAYER_X;
        } else {
            interface.displayInvalidMove();
            continue;
        }

        if (board.checkWin(PLAYER_X)) {
            clear();
            interface.playingBoard(PLAYER_X, board, false, true);
            interface.displayWinMessage(PLAYER_X);
            break;
        } else if (board.checkWin(PLAYER_O)) {
            clear();
            interface.playingBoard(PLAYER_X, board, false, true);
            interface.displayWinMessage(PLAYER_O);
            break;
        } else if (board.isFull()) {
            clear();
            interface.playingBoard(PLAYER_X, board, false, true);
            interface.displayDrawMessage();
            break;
        }
    }

    interface.displayGetBackToMenu();

}

/**
 * @brief Player vs bot game
 * @param mode 0 for non-threaded, 1 for threaded
 */
void Game::playerVsBot(int mode) {

    Board board;
    Bot bot;

    if (mode == 1){
        bot.setThreaded(true);
    }

    char currentPlayer = PLAYER_X;
    std::vector<std::pair<int, int>> executionTimes;

    while (true) {

        if (currentPlayer == PLAYER_X) {

            Move position = interface.playingBoard(currentPlayer, board);

            int row = position.getRow();
            int col = position.getCol();

            if (board.isEmpty(row, col)) {
                board.placeMove(row, col, PLAYER_X);
                currentPlayer = PLAYER_O;
            } else {
                interface.displayInvalidMove();
                continue;
            }
        } else {

            clear();
            
            interface.playingBoard(PLAYER_O, board, true);

            auto start = std::chrono::high_resolution_clock::now(); // Start measuring time
            Move botMove = bot.getBestMove(board, PLAYER_O);
            auto stop = std::chrono::high_resolution_clock::now();  // Stop measuring time

            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start); // Calculate duration

            executionTimes.push_back(std::make_pair(mode, duration.count()));

            board.placeMove(botMove.getRow(), botMove.getCol(), PLAYER_O);
            currentPlayer = PLAYER_X;

            flushinp(); // Flush input buffer
        }

        
        if (board.checkWin(PLAYER_X)) {
            clear();
            interface.playingBoard(PLAYER_X, board, false, true);
            interface.displayWinMessage(PLAYER_X);
            break;
        } else if (board.checkWin(PLAYER_O)) {
            clear();
            interface.playingBoard(PLAYER_X, board, false, true);
            interface.displayWinMessage(PLAYER_O);
            break;
        } else if (board.isFull()) {
            clear();
            interface.playingBoard(PLAYER_X, board, false, true);
            interface.displayDrawMessage();
            break;
        }
    }

    interface.displayExecutionTimes(executionTimes);
    saveExecutionTimes(executionTimes); 
}

/**
 * @brief Bot vs bot game
 * @param mode 0 for non-threaded, 1 for threaded
 */
void Game::botVsBot(int mode){
    
        Board board;
        Bot bot;
    
        if (mode == 1){
            bot.setThreaded(true);
        }
    
        char currentPlayer = PLAYER_X;

        std::vector<std::pair<int, int>> executionTimes;
    
        while (true) {
    
            if (currentPlayer == PLAYER_X) {
    
                clear();
    
                Move botMove = bot.getBestMove(board, PLAYER_X);
    
                board.placeMove(botMove.getRow(), botMove.getCol(), PLAYER_X);
                currentPlayer = PLAYER_O;
            } else {
    
                clear();

                auto start = std::chrono::high_resolution_clock::now(); // Start measuring time
                Move botMove = bot.getBestMove(board, PLAYER_O);
                auto stop = std::chrono::high_resolution_clock::now(); // Stop measuring time
                
                auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start); // Calculate duration

                executionTimes.push_back(std::make_pair(mode, duration.count()));
    
                board.placeMove(botMove.getRow(), botMove.getCol(), PLAYER_O);
                currentPlayer = PLAYER_X;
            }
    
            if (board.checkWin(PLAYER_X)) {
                break;
            } else if (board.checkWin(PLAYER_O)) {
                break;
            } else if (board.isFull()) {
                break;
            }

        }
    
    saveExecutionTimes(executionTimes);
    
}

void Game::saveExecutionTimes(std::vector<std::pair<int, int>> executionTimes) {
    FileManager fileManager;
    std::vector<std::string> lines;

    // Save execution times to a file
    for (const auto &[mode, time] : executionTimes) {
        std::string line = std::to_string(mode) + "," + std::to_string(time);
        lines.push_back(line);
    }
    fileManager.writeExecutionTimes("../executionTimes.csv", lines);
}

/**
 * @brief Simulates games
 * @param games Number of games to simulate
 * @param mode 0 for non-threaded, 1 for threaded
 */
void Game::simulateGames(int games, int mode) {
    for (int i = 0; i < games; i++) {
        botVsBot(mode);
    }
}