#include "interface.h"

Interface::Interface() {}

Interface::~Interface() {}

int Interface::menu() {

    int choice = 1; // Initially selected option

    while (true) {
        clear(); // Clear the screen

        attron(A_BOLD); // Bold text
        printw("\n _________  ___  ________               _________  ________  ________               _________  ________  _______");
        printw("\n|\\___   ___\\\\  \\|\\   ____\\             |\\___   ___\\\\   __  \\|\\   ____\\             |\\___   ___\\\\   __  \\|\\   ___\\");
        printw("\n\\|___ \\  \\_\\ \\  \\ \\  \\___|  ___________\\|___ \\  \\_\\ \\  \\|\\  \\ \\  \\___|  ___________\\|___ \\  \\_\\ \\  \\|\\  \\ \\  \\___");
        printw("\n     \\ \\  \\ \\ \\  \\ \\  \\    |\\____________\\  \\ \\  \\ \\ \\   __  \\ \\  \\    |\\____________\\  \\ \\  \\ \\ \\  \\\\\\  \\ \\   ___\\");
        printw("\n      \\ \\  \\ \\ \\  \\ \\  \\___\\|____________|   \\ \\  \\ \\ \\  \\ \\  \\ \\  \\___\\|____________|   \\ \\  \\ \\ \\  \\\\\\  \\ \\  \\___");
        printw("\n       \\ \\__\\ \\ \\__\\ \\_______\\                \\ \\__\\ \\ \\__\\ \\__\\ \\_______\\                \\ \\__\\ \\ \\_______\\ \\______\\");
        printw("\n        \\|__|  \\|__|\\|_______|                 \\|__|  \\|__|\\|__|\\|_______|                 \\|__|  \\|_______|\\|______|\n\n\n");
        attroff(A_BOLD); // Turn off bold text

        int numberOfChoices = 4;

        // Print options
        for (int i = 1; i <= numberOfChoices; ++i) {
            printw("      ");
            if (i == choice) {
                printw("=> ");
                attron(A_REVERSE); // Highlight current option
            }
            switch (i) {
            case 1:
                printw("Player vs Player\n");
                break;
            case 2:
                printw("Player vs Bot\n");
                break;
            case 3:
                printw("Credits\n");
                break;
            case 4:
                printw("Exit\n");
                break;
            }
            if (i == choice) {
                attroff(A_REVERSE); // Turn off highlighting
            }
        }

        int ch = getch(); // Wait for a key press

        if (ch == 'q' || ch == 'Q') {
            return numberOfChoices; // Exit the program
        } else if (ch == KEY_UP || ch == 'w' || ch == 'W') {
            if (choice == 1) {
                choice = numberOfChoices;
            } else {
                choice--;
            }
        } else if (ch == KEY_DOWN || ch == 's' || ch == 'S') {
            if (choice == numberOfChoices) {
                choice = 1;
            } else {
                choice++;
            }
        } else if (ch == '\n' && choice >= 1 && choice <= numberOfChoices) {
            return choice; // Return the selected option
        }

        refresh(); // Refresh the screen
    }
}

void Interface::displayGetBackToMenu() {
    printw("\n Press ANY KEY to go back to the menu...");
    refresh();
    getch(); // Wait for any key press
}

int Interface::botMenu() {

    int choice = 1; // Initially selected option

    const int numberOfChoices = 4;

    while (true) {
        clear(); // Clear the screen
        printw(" \n    Choose Bot Difficulty\n\n");
        // Print options
        for (int i = 1; i <= numberOfChoices; ++i) {
            printw("      ");
            if (i == choice) {
                printw("=> ");
                attron(A_REVERSE); // Highlight current option
            }
            switch (i) {
            case 1:
                printw("Impossible\n");
                break;
            case 2:
                printw("Impossible Threaded\n");
                break;
            case 3:
                printw("Generate Stadistics\n");
                break;
            case 4:
                printw("Go back\n");
                break;
            }
            if (i == choice) {
                attroff(A_REVERSE); // Turn off highlighting
            }
        }

        refresh();

        int ch = getch(); // Wait for a key press

        if (ch == 'q' || ch == 'Q') {
            return 4; // Exit the program
        } else if (ch == KEY_UP || ch == 'w' || ch == 'W') {
            if (choice == 1) {
                choice = numberOfChoices;
            } else {
                choice--;
            }
        } else if (ch == KEY_DOWN || ch == 's' || ch == 'S') {
            if (choice == numberOfChoices) {
                choice = 1;
            } else {
                choice++;
            }
        } else if (ch == '\n' && choice >= 1 && choice <= numberOfChoices) {
            return choice; // Return the selected option
        }
    }
}


int Interface::simulateGamesMenu() {

    int choice = 1; // Initially selected option

    const int numberOfChoices = 4;

    std::map<int, int> choices = {
        {1, 5},
        {2, 10},
        {3, 15},
        {4, 0}};

    while (true) {
        clear(); // Clear the screen
        printw(" \n    Choose the number of games to simulate\n\n");
        // Print options
        for (int i = 1; i <= numberOfChoices; ++i) {
            printw("      ");
            if (i == choice) {
                printw("=> ");
                attron(A_REVERSE); // Highlight current option
            }
            switch (i) {
            case 1:
                printw("5 game\n");
                break;
            case 2:
                printw("10 games\n");
                break;
            case 3:
                printw("15 games\n");
                break;
            case 4:
                printw("Go back\n");
                break;
            }
            if (i == choice) {
                attroff(A_REVERSE); // Turn off highlighting
            }
        }

        refresh();

        int ch = getch(); // Wait for a key press

        if (ch == KEY_UP || ch == 'w' || ch == 'W') {
            if (choice == 1) {
                choice = numberOfChoices;
            } else {
                choice--;
            }
        } else if (ch == KEY_DOWN || ch == 's' || ch == 'S') {
            if (choice == numberOfChoices) {
                choice = 1;
            } else {
                choice++;
            }
        } else if (ch == '\n' && choice >= 1 && choice <= numberOfChoices) {
            return choices[choice]; // Return the selected option
        }
    }

}

void Interface::displayCredits() {
    clear();
    printw("\n Developed by: \n\n");
    printw("   - Luis Fuentes Fuentes\n");
    printw("   - Andres Gonzalez Romero\n");
    printw("   - Gerick Vargas Camacho\n");
}

void Interface::displayGoodbye() {
    clear();
    printw("\n    Goodbye. Thank you for playing!\n");
}

void Interface::displayBoard(Board board) {

    // Constants
    const char EMPTY = ' ';
    const char PLAYER_X = 'X';
    const char PLAYER_O = 'O';

    // Board
    const std::string boardTop = "\n\n\n\n               ╔═════╦═════╦═════╗\n";
    const std::string boardBottom = "               ╚═════╩═════╩═════╝\n";
    const std::string boardMiddle = "               ╠═════╬═════╬═════╣\n";
    const std::string emptyCell = "   ";

    std::map<char, std::vector<std::string>> board_map = {
        {'X', {"█ █", " █ ", "█ █"}},
        {'O', {" █ ", "█ █", " █ "}},
        {' ', {"   ", "   ", "   "}}};

    for (int i = 0; i < 13; i++) {

        if (i == 0)
            printw("%s", boardTop.c_str());
        else if (i == 12)
            printw("%s", boardBottom.c_str());
        else if (i % 4 == 0)
            printw("%s", boardMiddle.c_str());
        else {

            for (int j = 0; j < 7; j++) {

                if (j == 0) {
                    printw("               ║ ");
                } else if (j == 6) {
                    printw(" ║\n");
                } else if (j % 2 == 0) {
                    printw(" ║ ");
                } else {
                    int row_index = (i - 1) / 4;
                    int col_index = (j - 1) / 2;

                    std::vector<std::vector<char>> currentBoard = board.getBoard();

                    if (currentBoard[row_index][col_index] != EMPTY) {
                        if (currentBoard[row_index][col_index] == PLAYER_O) {
                            attron(COLOR_PAIR(2));
                            printw("%s", board_map[currentBoard[row_index][col_index]][(i - 1) % 4].c_str());
                            attroff(COLOR_PAIR(2));
                        } else if (currentBoard[row_index][col_index] == PLAYER_X) {
                            attron(COLOR_PAIR(1));
                            printw("%s", board_map[currentBoard[row_index][col_index]][(i - 1) % 4].c_str());
                            attroff(COLOR_PAIR(1));
                        }
                    } else {
                        printw("%s", emptyCell.c_str());
                    }
                }
            }
        }
    }
}

int Interface::playingBoard(char player, Board board) {

    std::vector<int> currentPosition = board.getFirstAvailableMove();
    std::vector<int> newPosition = currentPosition;
    std::vector<int> invalidPosition = {-1, -1};

    std::map<std::vector<int>, int> positions = {
        {{0, 0}, 1},
        {{0, 1}, 2},
        {{0, 2}, 3},
        {{1, 0}, 4},
        {{1, 1}, 5},
        {{1, 2}, 6},
        {{2, 0}, 7},
        {{2, 1}, 8},
        {{2, 2}, 9}};

    while (true) {
        clear(); // Clear the screen

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

        printw("\n\n                 Player %c's turn\n\n", player);

        for (int i = 0; i < 13; i++) {

            if (i == 0)
                printw("%s", boardTop.c_str());
            else if (i == 12)
                printw("%s", boardBottom.c_str());
            else if (i % 4 == 0)
                printw("%s", boardMiddle.c_str());
            else {

                for (int j = 0; j < 7; j++) {

                    if (j == 0) {
                        printw("               ║ ");
                    } else if (j == 6) {
                        printw(" ║\n");
                    } else if (j % 2 == 0) {
                        printw(" ║ ");
                    } else {
                        int row_index = (i - 1) / 4;
                        int col_index = (j - 1) / 2;

                        std::vector<std::vector<char>> currentBoard = board.getBoard();

                        if (row_index == currentPosition[0] && col_index == currentPosition[1]) {
                            if (player == PLAYER_X) {
                                attron(COLOR_PAIR(1));
                                attron(A_BLINK);
                                printw("%s", board_map[player][(i - 1) % 4].c_str());
                                attroff(A_BLINK);
                                attroff(COLOR_PAIR(1));
                            } else if (player == PLAYER_O) {
                                attron(COLOR_PAIR(2));
                                attron(A_BLINK);
                                printw("%s", board_map[player][(i - 1) % 4].c_str());
                                attroff(A_BLINK);
                                attroff(COLOR_PAIR(2));
                            }
                        } else if (currentBoard[row_index][col_index] != EMPTY) {
                            if (currentBoard[row_index][col_index] == PLAYER_O) {
                                attron(COLOR_PAIR(2));
                                printw("%s", board_map[currentBoard[row_index][col_index]][(i - 1) % 4].c_str());
                                attroff(COLOR_PAIR(2));
                            } else if (currentBoard[row_index][col_index] == PLAYER_X) {
                                attron(COLOR_PAIR(1));
                                printw("%s", board_map[currentBoard[row_index][col_index]][(i - 1) % 4].c_str());
                                attroff(COLOR_PAIR(1));
                            }
                        } else {
                            printw("%s", emptyCell.c_str());
                        }
                    }
                }
            }
        }

        //-----------------------------------------------------------------------------------------------------
        refresh();

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

    return positions[currentPosition];
}

int Interface::playerTurn(char player, Board board) {
    int position;

    clear(); // Clear the screen

    char input = playingBoard(player, board);

    position = input - '0' + 48;

    return position;
}

void Interface::displayInvalidMove() {
    printw("\n             Invalid move! Try again");
    refresh();
    getch(); // Wait for any key press
}

void Interface::displayWinMessage(char player) {

    player == 'X' ? attron(COLOR_PAIR(1)) : attron(COLOR_PAIR(2)); // Turn on color pair 1 (red) or 2 (blue)
    printw("\n                 ╔═════════════╗");
    printw("\n                 ║Player %c wins║", player);
    printw("\n                 ╚═════════════╝\n");
    player == 'X' ? attroff(COLOR_PAIR(1)) : attroff(COLOR_PAIR(2)); // Turn off color pair 1 or 2
}

void Interface::displayDrawMessage() {
    printw("\n                  ╔═══════════╗");
    printw("\n                  ║It's a draw║");
    printw("\n                  ╚═══════════╝\n");
}

void Interface::displayExecutionTimes(std::vector<std::pair<int, int>> executionTimes) {
    attron(COLOR_PAIR(3)); // Turn on color pair 2 (green)
    printw("\n          ╔════════════════════════════╗");
    printw("\n          ║Bot movement execution times║");
    printw("\n          ╠════════════════════════════╣\n");
    for (const auto &[_, executionTimes] : executionTimes) {
        printw("          ║%10d microseconds%5s║\n", executionTimes, "");
    }
    printw("          ╚════════════════════════════╝\n");
    attroff(COLOR_PAIR(3)); // Turn off color pair 2
}

void Interface::displayStats() {

    clear(); // Clear the screen

    FileManager fileManager;

    std::vector<std::pair<int, int>> executionTimes = fileManager.readExecutionTimes("../executionTimes.csv");

    if (executionTimes.empty()) {
        printw(" NO STATS AVAILABLE\n");
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

    displayExecutionTimesBarChart(averageExecutionTimes);

    printw("\n\n");
    printw("%9sThe average execution time of the non-threaded version is ", ""); 
    attron(A_UNDERLINE); // Underline text
    attron(A_BOLD); // Bold text
    printw("%.2f", nonThreadedAverage);
    attroff(A_BOLD); // Turn off bold text
    attroff(A_UNDERLINE); // Turn off underline text
    printw(" microseconds.\n");

    printw("%9sThe average execution time of the threaded version is ", "");
    attron(A_UNDERLINE); // Underline text
    attron(A_BOLD); // Bold text
    printw("%.2f", threadedAverage);
    attroff(A_BOLD); // Turn off bold text
    attroff(A_UNDERLINE); // Turn off underline text

    printw(" microseconds.\n");

    printw("%9sThe threaded version achieves a speedup of ", "");
    attron(A_UNDERLINE); // Underline text
    attron(A_BOLD); // Bold text
    printw("%.2f%%", efficiency);
    attroff(A_BOLD); // Turn off bold text
    attroff(A_UNDERLINE); // Turn off underline text
    printw(".\n\n");

    printw("%9s» Efficiency is an important metric to consider when evaluating the performance\n", ""); 
    printw("%9s  of different implementations.\n", "");
    printw("%9s» A higher efficiency indicates that the threaded version is able to perform the\n", ""); 
    printw("%9s  same task in less time compared to the non-threaded version.\n", "");
    printw("%9s» This can be beneficial in scenarios where performance is critical, such as\n", ""); 
    printw("%9s  real-time systems or computationally intensive tasks.\n", "");
        

    refresh();
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
    attron(A_UNDERLINE); // Underline text
    attron(A_BOLD);      // Bold text
    printw("Execution times bar chart (in microseconds)\n\n");
    attroff(A_BOLD); // Turn off bold text
    attroff(A_UNDERLINE); // Turn off underline text


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

    // printw("%8s │                                 \n", "");
    // printw("%8d │-----┌──────┐--------------------\n", max);
    // printw("%8s │     │      │                    \n", "");
    // printw("%8s │     │      │                    \n", "");
    // printw("%8s │     │      │                    \n", "");
    // printw("%8d │-----│      │--------┌──────┐----\n", min);
    // printw("%8s │     │      │        │      │    \n", "");
    // printw("%8s │     │      │        │      │    \n", "");
    // printw("%8s │     │      │        │      │    \n", "");
    // printw("%8s │     │      │        │      │    \n", "");
    // printw("%8s └─────┴──────┴────────┴──────┴────\n", "");
    // printw("%8s     Non-threaded      Threaded    \n", "");
}

void Interface::displayLoading() {
    clear();

    printw("%5s  _                     _ _                    \n", "");
    printw("%5s | |                   | (_)                   \n", "");
    printw("%5s | |     ___   __ _  __| |_ _ __   __ _        \n", "");
    printw("%5s | |    / _ \\ / _` |/ _` | | '_ \\ / _` |       \n", "");
    printw("%5s | |___| (_) | (_| | (_| | | | | | (_| |_ _ _  \n", "");
    printw("%5s |______\\___/ \\__,_|\\__,_|_|_| |_|\\__, (_|_|_) \n", "");
    printw("%5s                                   __/ |       \n", "");
    printw("%5s                                  |___/        \n", "");

    refresh();
}