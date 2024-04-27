#include "interface.h"

Interface::Interface() {}

Interface::~Interface() {}

int Interface::menu() {

    int choice = 1; // Initially selected option

    while (true) {
        clear(); // Clear the screen
        printw(" \n      Tic Tac Toe Game\n\n");
        // Print options
        for (int i = 1; i <= 4; ++i) {
            printw("      ");
            if (i == choice) {
                printw(" ");
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
            endwin(); // End ncurses
            return 4; // Exit the program
        } else if (ch == KEY_UP || ch == 'w' || ch == 'W') {
            if (choice == 1) {
                choice = 4;
            } else {
                choice--;
            }
        } else if (ch == KEY_DOWN || ch == 's' || ch == 'S') {
            if (choice == 4) {
                choice = 1;
            } else {
                choice++;
            }
        } else if (ch == '\n' && choice >= 1 && choice <= 4) {
            return choice; // Return the selected option
        }

        refresh(); // Refresh the screen
    }
}

void Interface::displayGetBackToMenu() {
    printw("\n Press ANY KEY to go back to the main menu...");
    refresh();
    getch(); // Wait for any key press
}

int Interface::botMode() {

    int choice = 1; // Initially selected option

    while (true) {
        clear(); // Clear the screen
        printw(" \n    Choose Bot Difficulty\n\n");
        // Print options
        for (int i = 1; i <= 3; ++i) {
            printw("      ");
            if (i == choice) {
                printw(" ");
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
            endwin(); // End ncurses
            return 4; // Exit the program
        } else if (ch == KEY_UP || ch == 'w' || ch == 'W') {
            if (choice == 1) {
                choice = 3;
            } else {
                choice--;
            }
        } else if (ch == KEY_DOWN || ch == 's' || ch == 'S') {
            if (choice== 3) {
                choice = 1;
            } else {
                choice++;
            }
        } else if (ch == '\n' && choice >= 1 && choice <= 3) {
            endwin();      // End ncurses
            return choice; // Return the selected option
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
    const std::string boardTop = "\n\n               ╔═════╦═════╦═════╗\n";
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

void Interface::displayExecutionTimes(std::vector<int> executionTimes) {
    attron(COLOR_PAIR(3)); // Turn on color pair 2 (green)
    printw("\n          ╔════════════════════════════╗");
    printw("\n          ║Bot movement execution times║");
    printw("\n          ╠════════════════════════════╣\n");
    for (int i = 0; i < executionTimes.size(); i++) {
        printw("          ║%10d microseconds%5s║\n", executionTimes[i], "");
    }
    printw("          ╚════════════════════════════╝\n");
    attroff(COLOR_PAIR(3)); // Turn off color pair 2
}