#ifndef INTERFACE_H
#define INTERFACE_H

#include <iostream>
#include <limits>
#include <vector>
#include <map>
#include <iomanip>



class Interface {

public:
    Interface();
    ~Interface();
    int displayMenu();
    int displayBotMode();
    void displayCredits();
    void displayBoard(std::vector<std::vector<char>> board);
    void goodbye();
    void displayWinMessage(char player);
    void displayDrawMessage();
    void displayExecutionTimes(std::vector<int> executionTimes);

private:
    void clearScreen();
};

#endif // INTERFACE_H