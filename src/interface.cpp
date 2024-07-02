#include "interface.h"

Interface::Interface() {}

Interface::~Interface() {}

/**
 * @brief Displays the menu ASCII art.
 */
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

/**
 * @brief Displays the loading ASCII art.
 */
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

/**
 * @brief Displays the running simulation ASCII art.
 */
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

/**
 * @brief Displays the get back to menu message.
 */
void Interface::displayGetBackToMenu() {

    attron(COLOR_PAIR(1)); 
    printw("\n                         Press ANY KEY to go back to the menu...");
    attroff(COLOR_PAIR(1));

    refresh();

    getch();
}

/**
 * @brief Displays the credits.
 */
void Interface::displayCredits() {
    clear();

    displayMenuAsciiArt();

    attron(COLOR_PAIR(1)); 

    printw("                         Developed by: \n\n");
    printw("                            - Luis Fuentes Fuentes\n");
    printw("                            - Andres Gonzalez Romero\n");
    printw("                            - Gerick Vargas Camacho\n");

    attroff(COLOR_PAIR(1));

    displayGetBackToMenu();
}

/**
 * @brief Displays if the move is invalid.
 */
void Interface::displayInvalidMove() {
    attron(COLOR_PAIR(1));
    printw("\n                                Invalid move! Try again");
    attroff(COLOR_PAIR(1));
    refresh();
    getch();
}

/**
 * @brief Displays the win message.
 */
void Interface::displayWinMessage(char player) {

    const char PLAYER_X = 'X';
    const char PLAYER_O = 'O';

    int color = player == PLAYER_X ? 2 : 3; // Set color based on the player

    attron(COLOR_PAIR(color));
    printw("\n                                    ╔═════════════╗");
    printw("\n                                    ║Player %c wins║", player);
    printw("\n                                    ╚═════════════╝\n");
    attroff(COLOR_PAIR(color));
}

/**
 * @brief Displays the draw message.
 */
void Interface::displayDrawMessage() {
    
    attron(COLOR_PAIR(1));
    printw("\n                                     ╔═══════════╗");
    printw("\n                                     ║It's a draw║");
    printw("\n                                     ╚═══════════╝\n");
    attroff(COLOR_PAIR(1));
}

/**
 * @brief Displays the execution times.
 */
void Interface::displayExecutionTimes(std::vector<std::pair<int, int>> executionTimes) {
    attron(COLOR_PAIR(1));
    printw("\n                            ╔════════════════════════════╗");
    printw("\n                            ║Bot movement execution times║");
    printw("\n                            ╠════════════════════════════╣\n");
    for (const auto &[_, executionTimes] : executionTimes) {
        printw("                            ║%10d microseconds%5s║\n", executionTimes, "");
    }
    printw("                            ╚════════════════════════════╝\n");
    attroff(COLOR_PAIR(1));
}

/**
 * @brief Displays stats.
 */
void Interface::displayStats() {
    clear(); 

    FileManager fileManager;
    std::vector<std::pair<int, int>> executionTimes = fileManager.readExecutionTimes("../executionTimes.csv");

    // If there are no stats available, display a message and return
    if (executionTimes.empty()) {
        displayNoStatsMessage();
        return;
    }

    int nonThreadedDecisionsCount = 0;
    int threadedDecisionsCount = 0;
    double nonThreadedTotalTime = 0;
    double threadedTotalTime = 0;

    // Iterate over executionTimes to calculate counts and total times for threaded and non-threaded modes
    for (const auto &[mode, time] : executionTimes) {
        if (mode == 0) { // Non-threaded mode
            nonThreadedDecisionsCount++;
            nonThreadedTotalTime += time;
        } else { // Threaded mode
            threadedDecisionsCount++;
            threadedTotalTime += time;
        }
    }

    // Calculate averages for threaded and non-threaded modes
    double nonThreadedDecisionsAverage = calculateAverage(nonThreadedTotalTime, nonThreadedDecisionsCount);
    double threadedDecisionsAverage = calculateAverage(threadedTotalTime, threadedDecisionsCount);
    double efficiency = calculateEfficiency(threadedDecisionsAverage, nonThreadedDecisionsAverage);

    std::vector<std::pair<int, int>> averageExecutionTimes = {
        {0, nonThreadedDecisionsAverage},
        {1, threadedDecisionsAverage}};

    attron(COLOR_PAIR(1));
    displayExecutionTimesBarChart(averageExecutionTimes);
    displayAverageExecutionTimes(nonThreadedDecisionsAverage, threadedDecisionsAverage);
    displayEfficiency(efficiency);
    attroff(COLOR_PAIR(1));

    refresh();
    displayGetBackToMenu();
}

/**
 * @brief Displays a message when there are no stats available.
 */
void Interface::displayNoStatsMessage() {
    attron(COLOR_PAIR(1)); 
    printw(" NO STATS AVAILABLE\n");
    attroff(COLOR_PAIR(1));
}

/**
 * @brief Calculates the average time.
 */
double Interface::calculateAverage(double totalTime, int count) {
    return count > 0 ? totalTime / count : 0;
}

/**
 * @brief Calculates the efficiency.
 */
double Interface::calculateEfficiency(double threadedAverage, double nonThreadedAverage) {
    return (1 - (threadedAverage / nonThreadedAverage)) * 100;
}

/**
 * @brief Displays the average execution times.
 */
void Interface::displayAverageExecutionTimes(double nonThreadedAverage, double threadedAverage) {
    printw("\n\n");
    displayAverageExecutionTime("non-threaded", nonThreadedAverage);
    displayAverageExecutionTime("threaded", threadedAverage);
}

/**
 * @brief Displays the average execution time.
 */
void Interface::displayAverageExecutionTime(const std::string& mode, double averageTime) {
    printw("%9sThe average execution time of the %s version is ", "", mode.c_str());
    attron(A_UNDERLINE | A_BOLD);
    printw("%.2f", averageTime);
    attroff(A_UNDERLINE | A_BOLD);
    printw(" microseconds.\n");
}

/**
 * @brief Displays the efficiency.
 */
void Interface::displayEfficiency(double efficiency) {
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
}

/**
 * @brief Displays the execution times bar chart.
 */
void Interface::displayExecutionTimesBarChart(std::vector<std::pair<int, int>> averageExecutionTimes) {

    int nonThreaded = averageExecutionTimes[0].second;
    int threaded = averageExecutionTimes[1].second;

    int max = round(std::max(nonThreaded, threaded));
    int min = round(std::min(nonThreaded, threaded));

    int rounder = 500;

    int maxRounded = round(max / rounder) * rounder;
    int minRounded = round(min / rounder) * rounder;

    int midRounded = round((max - min) / rounder) * rounder;

    printw("\n\n%25s", "");
    attron(A_UNDERLINE | A_BOLD);
    printw("Execution times bar chart (in microseconds)\n\n");
    attroff(A_UNDERLINE | A_BOLD);

    printw("%31s │\n", "");
    for (int i = maxRounded; i > 0; i -= rounder) {
        if (maxRounded == i) {
            printw("%16s%15d │-----┌──────┐--------------------\n", "", max);
        } else if (minRounded == i) {
            printw("%16s%15d │-----│░▒▓▓▒░│--------┌──────┐----\n", "", min);
        } else if (min > i) {
            printw("%31s │     │░▒▓▓▒░│        │░▒▓▓▒░│    \n", "");
        } else if (midRounded == i) {
            printw("%16s%15d │     │░▒▓▓▒░│                    \n", "", i);
        } else {
            printw("%31s │     │░▒▓▓▒░│                    \n", "");
        }
    }
    printw("%16s%15d └─────┴──────┴────────┴──────┴────\n", "", 0);
    printw("%31s     Non-threaded      Threaded    \n", "");

}

/**
 * @brief Displays the menu.
 */
int Interface::menu(std::vector<std::string> options, std::string menuMessage){
    int choice = 0;

    while(true){

        clear(); 
        int numOptions = options.size();

        displayMenuAsciiArt();

        attron(COLOR_PAIR(1)); 

        printw("                         %s\n\n", menuMessage.c_str());

        for(int i = 0; i < numOptions; i++){
            printw("                           ");
            if( i == choice ){
                attron(A_BOLD | A_BLINK);
                printw("=> ");
                printw("%s\n", options.at(i).c_str());
                attroff(A_BOLD | A_BLINK);
            } else {
                printw("%s\n", options.at(i).c_str());
            }
        }

        attroff(COLOR_PAIR(1));

        int input = getch();

        // Check if the user wants to quit
        if (input == 'q' || input == 'Q') {
            return numOptions;
        } else if (input == KEY_UP || input == 'w' || input == 'W') { // Move up

            // Go to the last option if the user presses up on the first option
            if (choice == 0) {
                choice = numOptions - 1;
            } else { // Move up
                choice--;
            }
        } else if (input == KEY_DOWN || input == 's' || input == 'S') { // Move down

            // Go back to the first option if the the user presses down on the last option
            if (choice == numOptions - 1) { 
                choice = 0;
            } else { // Move down
                choice++;
            }
        } else if (input == '\n') {
            return choice;
        }

        refresh();

    }
}

/**
 * @brief Displays the playing board.
 */
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
            printw("                         Use the arrow keys to navigate the board\n\n");
            attroff(COLOR_PAIR(1));
        } 

        if (botTurn && !gameOver) {
            attron(COLOR_PAIR(1));
            printw("    Bot is thinking...\n\n");
            attroff(COLOR_PAIR(1));
        }

        if (gameOver) {
            attron(COLOR_PAIR(1));
            printw("                                      Game over!\n\n");
            attroff(COLOR_PAIR(1));
        }

        const char EMPTY = ' ';
        const char PLAYER_X = 'X';
        const char PLAYER_O = 'O';

        const std::string boardTop = "                                  ╔═════╦═════╦═════╗\n";
        const std::string boardBottom = "                                  ╚═════╩═════╩═════╝\n";
        const std::string boardMiddle = "                                  ╠═════╬═════╬═════╣\n";
        const std::string emptyCell = "   ";

        // Map to store the representation of each cell in the board
        std::map<char, std::vector<std::string>> board_map = {
            {'X', {"█ █", " █ ", "█ █"}},
            {'O', {" █ ", "█ █", " █ "}},
            {' ', {"   ", "   ", "   "}}
        };

        attron(COLOR_PAIR(1));
        printw("\n                                    Player %c's turn\n\n", player);
        attroff(COLOR_PAIR(1));

        for (int i = 0; i < 13; i++) {

            if (i == 0) { // Top border
                attron(COLOR_PAIR(1));
                printw("%s", boardTop.c_str());
                attroff(COLOR_PAIR(1));
            } else if (i == 12) { // Bottom border
                attron(COLOR_PAIR(1));
                printw("%s", boardBottom.c_str());
                attroff(COLOR_PAIR(1));
            } else if (i % 4 == 0) { // Middle border
                attron(COLOR_PAIR(1));
                printw("%s", boardMiddle.c_str());
                attroff(COLOR_PAIR(1));
            } else {

                for (int j = 0; j < 7; j++) {

                    if (j == 0) { // Left border
                        attron(COLOR_PAIR(1));
                        printw("                                  ║ ");
                        attroff(COLOR_PAIR(1));
                    } else if (j == 6) { // Right border
                        attron(COLOR_PAIR(1)); 
                        printw(" ║\n"); 
                        attroff(COLOR_PAIR(1));
                    } else if (j % 2 == 0) { // Middle border
                        attron(COLOR_PAIR(1));
                        printw(" ║ ");
                        attroff(COLOR_PAIR(1));
                    } else { // Cell content
                        int row_index = (i - 1) / 4;
                        int col_index = (j - 1) / 2;

                        std::vector<std::vector<char>> currentBoard = board.getBoard();

                        // Check if the current cell is the current position
                        if (row_index == currentPosition[0] && col_index == currentPosition[1] && !gameOver && !botTurn) {
                            int color = player == PLAYER_X ? 2 : 3;
                            attron(COLOR_PAIR(color) | A_BLINK | A_BOLD);
                            printw("%s", board_map[player][(i - 1) % 4].c_str());
                            attroff(COLOR_PAIR(color) | A_BLINK | A_BOLD);
                        } else if (currentBoard[row_index][col_index] != EMPTY) { // Check if the current cell is not empty
                            int color = currentBoard[row_index][col_index] == PLAYER_X ? 2 : 3;
                            attron(COLOR_PAIR(color));
                            printw("%s", board_map[currentBoard[row_index][col_index]][(i - 1) % 4].c_str());
                            attroff(COLOR_PAIR(color));
                        } else { // Empty cell
                            printw("%s", emptyCell.c_str());
                        }
                    }
                }
            }
        }

        refresh();

        if (gameOver || botTurn) {
            break;
        }

        int ch = getch();

        // Check if the user wants to quit
        if (ch == '\n') {
            break;
        } else if (ch == KEY_UP || ch == 'w' || ch == 'W') { // Move up
            newPosition = board.getMoveUp(currentPosition);
            if (newPosition == invalidPosition) {
                displayInvalidMove();
            } else {
                currentPosition = newPosition;
            }

        } else if (ch == KEY_DOWN || ch == 's' || ch == 'S') { // Move down
            newPosition = board.getMoveDown(currentPosition);
            if (newPosition == invalidPosition) {
                displayInvalidMove();
            } else {
                currentPosition = newPosition;
            }

        } else if (ch == KEY_LEFT || ch == 'a' || ch == 'A') { // Move left
            newPosition = board.getMoveLeft(currentPosition);
            if (newPosition == invalidPosition) {
                displayInvalidMove();
            } else {
                currentPosition = newPosition;
            }

        } else if (ch == KEY_RIGHT || ch == 'd' || ch == 'D') { // Move right
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