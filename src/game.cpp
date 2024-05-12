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
    runMainMenu();       // Run the menu
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

    // -1 is the terminal default text or background color

    init_pair(1, COLOR_GREEN, -1);   //  Define color pair 0 (green) - Text color
    init_pair(2, COLOR_RED, -1);  // Define color pair 2 (red)
    init_pair(3, COLOR_BLUE, -1); // Define color pair 2 (blue)
}

void Game::endNcurses() {
    refresh();
    endwin();  // End ncurses
}

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

void Game::runSimulateGamesMenu() {

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

    simulateGames(numberOfGames, 0);
    simulateGames(numberOfGames, 1);

    flushinp(); // Flush input buffer

    interface.displayStats(); // Display stats
}

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

            // Sleep between 250 and 1000 milliseconds
            std::this_thread::sleep_for(std::chrono::milliseconds(250 + (rand() % 750)));

            auto start = std::chrono::high_resolution_clock::now();
            Move botMove = bot.getBestMove(board, PLAYER_O);
            auto stop = std::chrono::high_resolution_clock::now();

            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

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
    
                auto start = std::chrono::high_resolution_clock::now();
                Move botMove = bot.getBestMove(board, PLAYER_X);
                auto stop = std::chrono::high_resolution_clock::now();
    
                board.placeMove(botMove.getRow(), botMove.getCol(), PLAYER_X);
                currentPlayer = PLAYER_O;
            } else {
    
                clear();

                auto start = std::chrono::high_resolution_clock::now();
                Move botMove = bot.getBestMove(board, PLAYER_O);
                auto stop = std::chrono::high_resolution_clock::now();
                
                auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

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
    for (const auto &[mode, time] : executionTimes) {
        std::string line = std::to_string(mode) + "," + std::to_string(time);
        lines.push_back(line);
    }
    fileManager.writeExecutionTimes("../executionTimes.csv", lines);
}

void Game::simulateGames(int games, int mode) {
    for (int i = 0; i < games; i++) {
        botVsBot(mode);
    }
}