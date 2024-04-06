#ifndef INTERFACE_H
#define INTERFACE_H

#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <vector>

class Interface {

public:
    Interface();
    ~Interface();
    int menu();
    void displayGetBackToMenu();
    int botMode();
    void displayCredits();
    void displayBoard(std::vector<std::vector<char>> board);
    int playerTurn(char player, std::vector<std::vector<char>> board);
    void displayInvalidMove();
    void displayGoodbye();
    void displayWinMessage(char player);
    void displayDrawMessage();
    void displayExecutionTimes(std::vector<int> executionTimes);

private:
    void clearScreen();
};

#endif // INTERFACE_H