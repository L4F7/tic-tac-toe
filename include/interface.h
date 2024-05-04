#ifndef INTERFACE_H
#define INTERFACE_H

#include <cmath>
#include <iostream>
#include <map>
#include <ncurses.h>
#include <vector>

#include "board.h"
#include "fileManager.h"
#include "move.h"

class Interface {

public:
    Interface();
    ~Interface();
    void displayMenuAsciiArt();
    void displayLoading();
    void displaySimulating();
    int menu(std::vector<std::string> options, std::string menuMessage);
    void displayGetBackToMenu();
    void displayCredits();
    Move playingBoard(char player, Board board, bool botTurn = false, bool gameOver = false);
    void displayInvalidMove();
    void displayWinMessage(char player);
    void displayDrawMessage();
    void displayExecutionTimes(std::vector<std::pair<int, int>> executionTimes);
    void displayStats();
    void displayExecutionTimesBarChart(std::vector<std::pair<int, int>> executionTimes);
};

#endif // INTERFACE_H