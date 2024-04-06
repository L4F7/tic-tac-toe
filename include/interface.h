#ifndef INTERFACE_H
#define INTERFACE_H

#include <iostream>
#include <limits>
#include <vector>
#include <map>
#include <iomanip>
#include <thread>
#include <chrono>

class Interface {

public:
    Interface();
    ~Interface();
    int displayMenuAndGetChoice();
    void displayGetBackToMenu();
    int displayBotModeAndGetChoice();
    void displayCredits();
    void displayBoard(std::vector<std::vector<char>> board);
    int displayPlayerTurnAndGetChoice(char player, std::vector<std::vector<char>> board);
    void displayInvalidMove();
    void displayGoodbye();
    void displayWinMessage(char player);
    void displayDrawMessage();
    void displayExecutionTimes(std::vector<int> executionTimes);

private:
    void clearScreen();
};

#endif // INTERFACE_H