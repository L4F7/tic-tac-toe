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

    const std::string boardTop = "    ╔═════╦═════╦═════╗    ╔═════╦═════╦═════╗\n";
    const std::string boardBottom = "    ╚═════╩═════╩═════╝    ╚═════╩═════╩═════╝\n";
    const std::string boardMiddle = "    ╠═════╬═════╬═════╣    ╠═════╬═════╬═════╣\n";
    const std::string emptyCell = "   ";

    // Colors
    const std::string strikethroughDarkRed = "\033[91m\033[9m";
    const std::string strikethroughDarkBlue = "\033[9m\033[94m";
    const std::string redColor = "\033[31m";
    const std::string blueColor = "\033[34m";
    const std::string whiteColor = "\033[39m";
    const std::string colorReset = "\e[0m";

    std::map<char, std::vector<std::string>> board_map = {
        {'X', {"█ █", " █ ", "█ █"}},
        {'O', {" █ ", "█ █", " █ "}},
        {' ', {"   ", "   ", "   "}}};

    for (int i = 0; i < 13; i++) {

        if (i == 0)
            std::cout << boardTop;
        else if (i == 12)
            std::cout << boardBottom;
        else if (i % 4 == 0)
            std::cout << boardMiddle;
        else {

            for (int j = 0; j < 7; j++) {

                if (j == 0) {
                    std::cout << "    ║ ";
                } else if (j == 6) {
                    std::cout << " ║";
                    std::cout << "    ";
                    if (i % 2 == 0) {
                        int row_index = (i - 1) / 4;
                        int col_index = (j - 1) / 2;

                        int firstCell = board[row_index][col_index - 2];
                        int secondCell = board[row_index][col_index - 1];
                        int thirdCell = board[row_index][col_index];

                        std::string firstColor = (firstCell == PLAYER_O) ? strikethroughDarkBlue : ((firstCell == PLAYER_X) ? strikethroughDarkRed : whiteColor);
                        std::string secondColor = (secondCell == PLAYER_O) ? strikethroughDarkBlue : ((secondCell == PLAYER_X) ? strikethroughDarkRed : whiteColor);
                        std::string thirdColor = (thirdCell == PLAYER_O) ? strikethroughDarkBlue : ((thirdCell == PLAYER_X) ? strikethroughDarkRed : whiteColor);


                        int num = i - row_index - 1;

                        std::string firstCellStr = firstColor + std::to_string(num) + colorReset;
                        std::string secondCellStr = secondColor + std::to_string(num + 1) + colorReset;
                        std::string thirdCellStr = thirdColor + std::to_string(num + 2) + colorReset;

                        std::cout << "║  " << firstCellStr << "  ║  " << secondCellStr << "  ║  " << thirdCellStr << "  ║\n";

                    } else {
                        std::cout << "║     ║     ║     ║\n";
                    }
                } else if (j % 2 == 0) {
                    std::cout << " ║ ";
                } else {
                    int row_index = (i - 1) / 4;
                    int col_index = (j - 1) / 2;

                    std::string color = redColor;

                    if (board[row_index][col_index] != EMPTY) {
                        if (board[row_index][col_index] == PLAYER_O)
                            color = blueColor;
                        std::cout << color << board_map[board[row_index][col_index]][(i - 1) % 4] << colorReset;
                    } else {
                        std::cout << emptyCell;
                    }
                }
            }
        }
    }
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