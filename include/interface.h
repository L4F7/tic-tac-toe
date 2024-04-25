#ifndef INTERFACE_H
#define INTERFACE_H

#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <ncurses.h>
#include <vector>

#include "board.h"

class Interface {

public:
    Interface();
    ~Interface();
    int menu();
    void displayGetBackToMenu();
    int botMode();
    void displayCredits();
    void displayBoard(Board board);
    int playingBoard(char player, Board board);
    int playerTurn(char player, Board board);
    void displayInvalidMove();
    void displayGoodbye();
    void displayWinMessage(char player);
    void displayDrawMessage();
    void displayExecutionTimes(std::vector<int> executionTimes);
};

#endif // INTERFACE_H