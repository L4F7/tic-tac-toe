#ifndef INTERFACE_H
#define INTERFACE_H

#include <cmath>
#include <iostream>
#include <map>
#include <ncurses.h>
#include <vector>

#include "board.h"
#include "fileManager.h"

class Interface {

public:
    Interface();
    ~Interface();
    int menu();
    void displayGetBackToMenu();
    int botMenu();
    int simulateGamesMenu();
    void displayCredits();
    void displayBoard(Board board);
    int playingBoard(char player, Board board);
    int playerTurn(char player, Board board);
    void displayInvalidMove();
    void displayGoodbye();
    void displayWinMessage(char player);
    void displayDrawMessage();
    void displayExecutionTimes(std::vector<std::pair<int, int>> executionTimes);
    void displayStats();
    void displayExecutionTimesBarChart(std::vector<std::pair<int, int>> executionTimes);
    void displayLoading();
};

#endif // INTERFACE_H