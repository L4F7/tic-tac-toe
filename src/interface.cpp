#include "interface.h"

Interface::Interface() {}

Interface::~Interface() {}

void Interface::displayMenuAsciiArt() {
    attron(COLOR_PAIR(1));
    printw("\n");
    printw("%5s████████ ██  ██████       ████████  █████   ██████       ████████  ██████  ███████ \n", "");
    printw("%5s   ██    ██ ██               ██    ██   ██ ██               ██    ██    ██ ██      \n", "");
    printw("%5s   ██    ██ ██      █████    ██    ███████ ██      █████    ██    ██    ██ █████   \n", "");
    printw("%5s   ██    ██ ██               ██    ██   ██ ██               ██    ██    ██ ██      \n", "");
    printw("%5s   ██    ██  ██████          ██    ██   ██  ██████          ██     ██████  ███████ \n", "");
    printw("\n");
    attroff(COLOR_PAIR(1));

    // Reference: https://patorjk.com/software/taag/#p=display&f=ANSI%20Regular&t=TIC-TAC-TOE
    
}

void Interface::displayLoading() {
    clear();

    attron(COLOR_PAIR(1));
    printw("\n");
    printw("%5s██       ██████   █████  ██████  ██ ███    ██  ██████           \n", "");
    printw("%5s██      ██    ██ ██   ██ ██   ██ ██ ████   ██ ██                \n", "");
    printw("%5s██      ██    ██ ███████ ██   ██ ██ ██ ██  ██ ██   ███          \n", "");
    printw("%5s██      ██    ██ ██   ██ ██   ██ ██ ██  ██ ██ ██    ██          \n", "");
    printw("%5s███████  ██████  ██   ██ ██████  ██ ██   ████  ██████  ██ ██ ██ \n", "");
    printw("\n");
    attroff(COLOR_PAIR(1));

    // Reference: https://patorjk.com/software/taag/#p=display&f=ANSI%20Regular&t=LOADING...
}

void Interface::displaySimulating(){
    clear();

    attron(COLOR_PAIR(1));
    printw("\n");
    printw("%5s██████  ██    ██ ███    ██ ███    ██ ██ ███    ██  ██████                              \n", "");
    printw("%5s██   ██ ██    ██ ████   ██ ████   ██ ██ ████   ██ ██                                   \n", "");
    printw("%5s██████  ██    ██ ██ ██  ██ ██ ██  ██ ██ ██ ██  ██ ██   ███                             \n", "");
    printw("%5s██   ██ ██    ██ ██  ██ ██ ██  ██ ██ ██ ██  ██ ██ ██    ██                             \n", "");
    printw("%5s██   ██  ██████  ██   ████ ██   ████ ██ ██   ████  ██████                              \n", "");
    printw("%5s                                                                                       \n", "");
    printw("%5s                                                                                       \n", "");
    printw("%5s███████ ██ ███    ███ ██    ██ ██       █████  ████████ ██  ██████  ███    ██          \n", "");
    printw("%5s██      ██ ████  ████ ██    ██ ██      ██   ██    ██    ██ ██    ██ ████   ██          \n", "");
    printw("%5s███████ ██ ██ ████ ██ ██    ██ ██      ███████    ██    ██ ██    ██ ██ ██  ██          \n", "");
    printw("%5s     ██ ██ ██  ██  ██ ██    ██ ██      ██   ██    ██    ██ ██    ██ ██  ██ ██          \n", "");
    printw("%5s███████ ██ ██      ██  ██████  ███████ ██   ██    ██    ██  ██████  ██   ████ ██ ██ ██ \n", "");
    printw("\n");
    attroff(COLOR_PAIR(1));

    // https://patorjk.com/software/taag/#p=display&f=ANSI%20Regular&t=RUNNING%0ASIMULATION...

}

int Interface::menu(std::vector<std::string> options, std::string menuMessage){
    int choice = 0; // Default selected option

    while(true){

        clear(); 
        int numOptions = options.size();

        displayMenuAsciiArt();

        attron(COLOR_PAIR(1)); 

        printw("    %s\n\n", menuMessage.c_str());

        //Print options
        for(int i = 0; i < numOptions; i++){
            printw("      ");
            if( i == choice ){
                printw("=> ");
                attron(A_STANDOUT);
                printw("%s\n", options.at(i).c_str());
                attroff(A_STANDOUT);
            } else {
                printw("%s\n", options.at(i).c_str());
            }
        }

        attroff(COLOR_PAIR(1));

        int input = getch(); // Wait for a key press

        if (input == 'q' || input == 'Q') {
            return numOptions; // Exit the program
        } else if (input == KEY_UP || input == 'w' || input == 'W') {
            if (choice == 0) {
                choice = numOptions - 1;
            } else {
                choice--;
            }
        } else if (input == KEY_DOWN || input == 's' || input == 'S') {
            if (choice == numOptions - 1) {
                choice = 0;
            } else {
                choice++;
            }
        } else if (input == '\n') {
            return choice; // Return the selected option
        }

        refresh();

    }
}

void Interface::displayGetBackToMenu() {

    attron(COLOR_PAIR(1)); 
    printw("\n Press ANY KEY to go back to the menu...");
    attroff(COLOR_PAIR(1));

    refresh();

    getch(); // Wait for any key press
}

void Interface::displayCredits() {
    clear();

    displayMenuAsciiArt();

    attron(COLOR_PAIR(1)); 

    printw("\n Developed by: \n\n");
    printw("   - Luis Fuentes Fuentes\n");
    printw("   - Andres Gonzalez Romero\n");
    printw("   - Gerick Vargas Camacho\n");

    attroff(COLOR_PAIR(1));

    displayGetBackToMenu();
}

Move Interface::playingBoard(char player, Board board, bool botTurn, bool gameOver) {

    std::vector<int> currentPosition = board.getFirstAvailableMove();
    std::vector<int> newPosition = currentPosition;
    std::vector<int> invalidPosition = {-1, -1};

    while (true) {
        clear(); 

        attron(COLOR_PAIR(1));
        displayMenuAsciiArt();
        attroff(COLOR_PAIR(1));

        if (!botTurn && !gameOver) {
            attron(COLOR_PAIR(1));
            printw("    Use the arrow keys to navigate the board\n\n");
            attroff(COLOR_PAIR(1));
        } 

        if (botTurn && !gameOver) {
            attron(COLOR_PAIR(1));
            printw("    Bot is thinking...\n\n");
            attroff(COLOR_PAIR(1));
        }

        if (gameOver) {
            attron(COLOR_PAIR(1));
            printw("    Game over!\n\n");
            attroff(COLOR_PAIR(1));
        }

        //-----------------------------------------------------------------------------------------------------

        // Constants
        const char EMPTY = ' ';
        const char PLAYER_X = 'X';
        const char PLAYER_O = 'O';

        // Board
        const std::string boardTop = "               ╔═════╦═════╦═════╗\n";
        const std::string boardBottom = "               ╚═════╩═════╩═════╝\n";
        const std::string boardMiddle = "               ╠═════╬═════╬═════╣\n";
        const std::string emptyCell = "   ";

        std::map<char, std::vector<std::string>> board_map = {
            {'X', {"█ █", " █ ", "█ █"}},
            {'O', {" █ ", "█ █", " █ "}},
            {' ', {"   ", "   ", "   "}}};

        attron(COLOR_PAIR(1));
        printw("\n\n                 Player %c's turn\n\n", player);
        attroff(COLOR_PAIR(1));

        for (int i = 0; i < 13; i++) {

            if (i == 0) {
                attron(COLOR_PAIR(1));
                printw("%s", boardTop.c_str());
                attroff(COLOR_PAIR(1));
            } else if (i == 12) {
                attron(COLOR_PAIR(1));
                printw("%s", boardBottom.c_str());
                attroff(COLOR_PAIR(1));
            } else if (i % 4 == 0) {
                attron(COLOR_PAIR(1));
                printw("%s", boardMiddle.c_str());
                attroff(COLOR_PAIR(1));
            } else {

                for (int j = 0; j < 7; j++) {

                    if (j == 0) {
                        attron(COLOR_PAIR(1));
                        printw("               ║ ");
                        attroff(COLOR_PAIR(1));
                    } else if (j == 6) {
                        attron(COLOR_PAIR(1));
                        printw(" ║\n");
                        attroff(COLOR_PAIR(1));
                    } else if (j % 2 == 0) {
                        attron(COLOR_PAIR(1));
                        printw(" ║ ");
                        attroff(COLOR_PAIR(1));
                    } else {
                        int row_index = (i - 1) / 4;
                        int col_index = (j - 1) / 2;

                        std::vector<std::vector<char>> currentBoard = board.getBoard();

                        if (row_index == currentPosition[0] && col_index == currentPosition[1] && !gameOver && !botTurn) {
                            int color = player == PLAYER_X ? 2 : 3;
                            attron(COLOR_PAIR(color) | A_BLINK | A_BOLD);
                            printw("%s", board_map[player][(i - 1) % 4].c_str());
                            attroff(COLOR_PAIR(color) | A_BLINK | A_BOLD);
                        } else if (currentBoard[row_index][col_index] != EMPTY) {
                            int color = currentBoard[row_index][col_index] == PLAYER_X ? 2 : 3;
                            attron(COLOR_PAIR(color));
                            printw("%s", board_map[currentBoard[row_index][col_index]][(i - 1) % 4].c_str());
                            attroff(COLOR_PAIR(color));
                        } else {
                            printw("%s", emptyCell.c_str());
                        }
                    }
                }
            }
        }

        //-----------------------------------------------------------------------------------------------------
        refresh();

        if (gameOver || botTurn) {
            break;
        }

        int ch = getch(); // Wait for a key press

        if (ch == '\n') {
            break;
        } else if (ch == KEY_UP || ch == 'w' || ch == 'W') {
            newPosition = board.getMoveUp(currentPosition);
            if (newPosition == invalidPosition) {
                displayInvalidMove();
            } else {
                currentPosition = newPosition;
            }

        } else if (ch == KEY_DOWN || ch == 's' || ch == 'S') {
            newPosition = board.getMoveDown(currentPosition);
            if (newPosition == invalidPosition) {
                displayInvalidMove();
            } else {
                currentPosition = newPosition;
            }

        } else if (ch == KEY_LEFT || ch == 'a' || ch == 'A') {
            newPosition = board.getMoveLeft(currentPosition);
            if (newPosition == invalidPosition) {
                displayInvalidMove();
            } else {
                currentPosition = newPosition;
            }

        } else if (ch == KEY_RIGHT || ch == 'd' || ch == 'D') {
            newPosition = board.getMoveRight(currentPosition);
            if (newPosition == invalidPosition) {
                displayInvalidMove();
            } else {
                currentPosition = newPosition;
            }
        }
    }

    return Move(currentPosition[0], currentPosition[1]);
}

void Interface::displayInvalidMove() {
    printw("\n             Invalid move! Try again");
    refresh();
    getch(); // Wait for any key press
}

void Interface::displayWinMessage(char player) {

    // Constants
    const char PLAYER_X = 'X';
    const char PLAYER_O = 'O';

    int color = player == PLAYER_X ? 2 : 3;

    attron(COLOR_PAIR(color)); // Turn on color pair 2 (red) or 3 (blue)
    printw("\n                 ╔═════════════╗");
    printw("\n                 ║Player %c wins║", player);
    printw("\n                 ╚═════════════╝\n");
    attroff(COLOR_PAIR(color)); // Turn off color pair 2 or 3
}

void Interface::displayDrawMessage() {
    
    attron(COLOR_PAIR(1));
    printw("\n                  ╔═══════════╗");
    printw("\n                  ║It's a draw║");
    printw("\n                  ╚═══════════╝\n");
    attroff(COLOR_PAIR(1));
}

void Interface::displayExecutionTimes(std::vector<std::pair<int, int>> executionTimes) {
    attron(COLOR_PAIR(1)); // Turn on color pair 2 (green)
    printw("\n          ╔════════════════════════════╗");
    printw("\n          ║Bot movement execution times║");
    printw("\n          ╠════════════════════════════╣\n");
    for (const auto &[_, executionTimes] : executionTimes) {
        printw("          ║%10d microseconds%5s║\n", executionTimes, "");
    }
    printw("          ╚════════════════════════════╝\n");
    attroff(COLOR_PAIR(1)); // Turn off color pair 2
}

void Interface::displayStats() {

    clear(); 

    FileManager fileManager;

    std::vector<std::pair<int, int>> executionTimes = fileManager.readExecutionTimes("../executionTimes.csv");

    if (executionTimes.empty()) {
        attron(COLOR_PAIR(1)); 
        printw(" NO STATS AVAILABLE\n");
        attroff(COLOR_PAIR(1));
        refresh();
        return;
    }

    int totalThreaded = 0;
    int totalNonThreaded = 0;
    double threadedAverage = 0;
    double nonThreadedAverage = 0;

    for (const auto &[mode, time] : executionTimes) {
        if (mode == 0) {
            totalNonThreaded++;
            nonThreadedAverage += time;
        } else {
            totalThreaded++;
            threadedAverage += time;
        }
    }

    nonThreadedAverage /= totalNonThreaded;
    threadedAverage /= totalThreaded;

    double efficiency = (1 - (threadedAverage / nonThreadedAverage)) * 100;

    std::vector<std::pair<int, int>> averageExecutionTimes = {
        {0, nonThreadedAverage},
        {1, threadedAverage}};

    attron(COLOR_PAIR(1)); // Turn on default text color

    displayExecutionTimesBarChart(averageExecutionTimes);

    printw("\n\n");
    printw("%9sThe average execution time of the non-threaded version is ", "");
    attron(A_UNDERLINE | A_BOLD);
    printw("%.2f", nonThreadedAverage);
    attroff(A_UNDERLINE | A_BOLD);
    printw(" microseconds.\n");

    printw("%9sThe average execution time of the threaded version is ", "");
    attron(A_UNDERLINE | A_BOLD);
    printw("%.2f", threadedAverage);
    attroff(A_UNDERLINE | A_BOLD);
    printw(" microseconds.\n");

    printw("%9sThe threaded version achieves a speedup of ", "");
    attron(A_UNDERLINE | A_BOLD);
    printw("%.2f%%", efficiency);
    attroff(A_UNDERLINE | A_BOLD);
    printw(".\n\n");

    printw("%9s» Efficiency is an important metric to consider when evaluating the performance\n", "");
    printw("%9s  of different implementations.\n", "");
    printw("%9s» A higher efficiency indicates that the threaded version is able to perform the\n", "");
    printw("%9s  same task in less time compared to the non-threaded version.\n", "");
    printw("%9s» This can be beneficial in scenarios where performance is critical, such as\n", "");
    printw("%9s  real-time systems or computationally intensive tasks.\n", "");

    attroff(COLOR_PAIR(1)); // Turn off default text color

    refresh();

    displayGetBackToMenu();

}

void Interface::displayExecutionTimesBarChart(std::vector<std::pair<int, int>> averageExecutionTimes) {

    int nonThreaded = averageExecutionTimes[0].second;
    int threaded = averageExecutionTimes[1].second;

    int max = round(std::max(nonThreaded, threaded));
    int min = round(std::min(nonThreaded, threaded));

    int rounder = 500;

    int maxRounded = round(max / rounder) * rounder;
    int minRounded = round(min / rounder) * rounder;

    int midRounded = round((max - min) / rounder) * rounder;

    printw("\n\n%9s", "");
    attron(A_UNDERLINE | A_BOLD);
    printw("Execution times bar chart (in microseconds)\n\n");
    attroff(A_UNDERLINE | A_BOLD);

    printw("%15s │\n", "");
    for (int i = maxRounded; i > 0; i -= rounder) {
        if (maxRounded == i) {
            printw("%15d │-----┌──────┐--------------------\n", max);
        } else if (minRounded == i) {
            printw("%15d │-----│░▒▓▓▒░│--------┌──────┐----\n", min);
        } else if (min > i) {
            printw("%15s │     │░▒▓▓▒░│        │░▒▓▓▒░│    \n", "");
        } else if (midRounded == i) {
            printw("%15d │     │░▒▓▓▒░│                    \n", i);
        } else {
            printw("%15s │     │░▒▓▓▒░│                    \n", "");
        }
    }
    printw("%15d └─────┴──────┴────────┴──────┴────\n", 0);
    printw("%15s     Non-threaded      Threaded    \n", "");

}