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
    
    int menu(std::vector<std::string> options, std::string menuMessage);
    Move playingBoard(char player, Board board, bool botTurn = false, bool gameOver = false);
private:
    double calculateAverage(double totalTime, int count);
    double calculateEfficiency(double threadedAverage, double nonThreadedAverage);
    void displayExecutionTimesBarChart(std::vector<std::pair<int, int>> executionTimes);
    void displayNoStatsMessage();
    void displayAverageExecutionTimes(double nonThreadedAverage, double threadedAverage);
    void displayAverageExecutionTime(const std::string &mode, double averageTime);
    void displayEfficiency(double efficiency);

};

#endif // INTERFACE_H