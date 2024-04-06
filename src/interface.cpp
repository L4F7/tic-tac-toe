#include "interface.h"

Interface::Interface() {}

Interface::~Interface() {}

void Interface::clearScreen() {
#if defined(_WIN32)
    system("cls");
#elif defined(__linux__)
    system("clear");
#endif
}

int Interface::menu() {
    int choice;
    while(true) {
        clearScreen();
        std::cout << " \n      Tic Tac Toe Game\n\n";
        std::cout << " 1. Player vs Player\n";
        std::cout << " 2. Player vs Bot\n";
        std::cout << " 3. Credits\n";
        std::cout << " 4. Exit\n";
        std::cout << "\n Enter your choice (1-4): ";
        std::cin >> choice; 
        
        if(std::cin.fail())  {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else {
            break;
        }
    }
    return choice;
}

void Interface::displayGetBackToMenu() {
    std::cout << "\n Press ENTER to go back to the main menu...";
    std::cin.ignore().get();
}

int Interface::botMode() {
    int choice;
    while(true) {
        clearScreen();
        std::cout << " \n    Choose Bot Difficulty\n\n";
        std::cout << " 1. Impossible\n";
        std::cout << " 2. Impossible Threaded\n";
        std::cout << " 3. Go back\n";
        std::cout << "\n Enter your choice (1-3): ";
        std::cin >> choice;
        
        if(std::cin.fail())  {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else {
            break;
        }
    }
    return choice;
}

void Interface::displayCredits() {
    clearScreen();
    std::cout << "\n Developed by: \n\n";
    std::cout << "   - Luis Fuentes Fuentes\n";
    std::cout << "   - Andres Gonzalez Romero\n";
    std::cout << "   - Gerick Vargas Camacho\n";
    displayGetBackToMenu();
}

void Interface::displayGoodbye() {
    clearScreen();
    std::cout << "\n    Goodbye. Thank you for playing!\n";
}


void Interface::displayBoard(std::vector<std::vector<char>> board) {

    clearScreen();

    const char EMPTY = ' ';
    const char PLAYER_X = 'X';
    const char PLAYER_O = 'O';

    std::map<char, std::vector<std::string>> board_map = {
        {'X', {"█ █", " █ ", "█ █"}},
        {'O', {" █ ", "█ █", " █ "}},
        {' ', {"   ", "   ", "   "}}};

    for (int i = 0; i < 13; i++) {

        if (i == 0)
            std::cout << "    ╔═════╦═════╦═════╗    ╔═════╦═════╦═════╗\n";
        else if (i == 12)
            std::cout << "    ╚═════╩═════╩═════╝    ╚═════╩═════╩═════╝\n";
        else if (i % 4 == 0)
            std::cout << "    ╠═════╬═════╬═════╣    ╠═════╬═════╬═════╣\n";
        else {

            for (int j = 0; j < 7; j++) {

                std::string color = "\033[31m";
                std::string colorEnd = "\e[0m";

                if (j == 0) {
                    std::cout << "    ║ ";
                } else if (j == 6) {
                    std::cout << " ║";
                    std::cout << "    ";
                    if (i % 2 == 0) {
                        int row_index = (i - 1) / 4;
                        int col_index = (j - 1) / 2;

                        std::string firstColor = "\033[39m";
                        std::string secondColor = "\033[39m";
                        std::string thirdColor = "\033[39m";

                        if (board[row_index][col_index - 2] == PLAYER_O)
                            firstColor = "\033[94m\033[9m";
                        else if (board[row_index][col_index - 2] == PLAYER_X)
                            firstColor = "\033[91m\033[9m";

                        if (board[row_index][col_index - 1] == PLAYER_O)
                            secondColor = "\033[94m\033[9m";
                        else if (board[row_index][col_index - 1] == PLAYER_X)
                            secondColor = "\033[91m\033[9m";

                        if (board[row_index][col_index] == PLAYER_O)
                            thirdColor = "\033[94m\033[9m";
                        else if (board[row_index][col_index] == PLAYER_X)
                            thirdColor = "\033[91m\033[9m";

                        int num = i - (i - 1) / 4 - 1;

                        std::cout << "║  " << firstColor << num << colorEnd << "  ║  " << secondColor << num + 1 << colorEnd << "  ║  " << thirdColor << num + 2 << colorEnd << "  ║\n";

                    } else {
                        std::cout << "║     ║     ║     ║\n";
                    }
                } else if (j % 2 == 0) {
                    std::cout << " ║ ";
                } else {
                    int row_index = (i - 1) / 4;
                    int col_index = (j - 1) / 2;
                    if (board[row_index][col_index] != EMPTY) {
                        if (board[row_index][col_index] == PLAYER_O)
                            color = "\033[34m";
                        std::cout << color << board_map[board[row_index][col_index]][(i - 1) % 4] << colorEnd;
                    } else {
                        std::cout << "   ";
                    }
                }
            }
        }
    }
    /*
    0  1  2  3  4  5  6
    ╔═════╦═════╦═════╗ 0
    ║     ║     ║     ║ 1
    ║  1  ║  2  ║  3  ║ 2       0-0 0-1 0-2
    ║     ║     ║     ║ 3
    ╠═════╬═════╬═════╣ 4
    ║     ║     ║     ║ 5
    ║  4  ║  5  ║  6  ║ 6       1-0 1-1 1-2
    ║     ║     ║     ║ 7
    ╠═════╬═════╬═════╣ 8
    ║     ║     ║     ║ 9
    ║  7  ║  8  ║  9  ║ 10      2-0 2-1 2-2
    ║     ║     ║     ║ 11
    ╚═════╩═════╩═════╝ 12
    */
}

int Interface::playerTurn(char player, std::vector<std::vector<char>> board) {
    
    int position;

    while (true) {
        displayBoard(board);
        std::cout << "\nPlayer " << player << "'s turn. \nEnter position (1-9): ";
        std::cin >> position;

        if (std::cin.fail() || position < 1 || position > 9) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else {
            break;
        }
    }

    return position;
}

void Interface::displayInvalidMove() {
    std::cout << "\nInvalid move! Press ENTER to try again...\n";
    std::cin.ignore().get();
}

void Interface::displayWinMessage(char player) {

    std::string color = "\033[91m";

    if (player == 'O')
        color = "\033[94m";

    std::cout << "\n                 " << color << "╔══════════════╗\033[0m";
    std::cout << "\n                 " << color << "║Player "<< player <<" wins!║\033[0m";
    std::cout << "\n                 " << color << "╚══════════════╝\033[0m\n";
}

void Interface::displayDrawMessage() {
    std::cout << "\n                  ╔════════════╗";
    std::cout << "\n                  ║It's a draw!║";
    std::cout << "\n                  ╚════════════╝\n";
}

void Interface::displayExecutionTimes(std::vector<int> executionTimes) {
    std::cout << "\n\033[92m          ╔════════════════════════════╗";
    std::cout << "\n          ║Bot movement execution times║";
    std::cout << "\n          ╠════════════════════════════╣\n";
    for (int i = 0; i < executionTimes.size(); i++) {
        std::cout << "          ║" << std::right << std::setw(10) << executionTimes[i] << std::left << std::setw(18) << " microseconds" << "║\n";
    }
    std::cout << "          ╚════════════════════════════╝\033[0m\n";
    displayGetBackToMenu();
}