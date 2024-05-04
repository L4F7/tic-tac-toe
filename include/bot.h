#ifndef BOT_H
#define BOT_H

#include <thread>
#include <vector>

#include "board.h"
#include "move.h"

class Bot {

public:
    Bot();
    ~Bot();

    void setThreaded(bool threaded);
    int getThreaded();

    Move getBestMove(Board &board, char playerToSimulate);
    Move getBestMoveNonThreaded(Board &board, char playerToSimulate);
    Move getBestMoveThreaded(Board &board, char playerToSimulate);

private:
    bool threaded;
    int minMax(Board &board, bool isMaximizing, char playerToSimulate);
};

#endif // BOT_H
