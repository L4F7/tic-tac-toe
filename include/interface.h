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
    void displayGetBackToMenu();
    void displayCredits();
    void displayInvalidMove();
    void displayWinMessage(char player);
    void displayDrawMessage();
    void displayExecutionTimes(std::vector<std::pair<int, int>> executionTimes);
    void displayStats();
    void displayExecutionTimesBarChart(std::vector<std::pair<int, int>> executionTimes);
    
    int menu(std::vector<std::string> options, std::string menuMessage);
    Move playingBoard(char player, Board board, bool botTurn = false, bool gameOver = false);
};

#endif // INTERFACE_H