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

    void setMode(int mode);
    int getMode();

    Move getBestMove(Board &board);
    Move getBestMoveNonThreaded(Board &board);
    Move getBestMoveThreaded(Board &board);

private:
    int mode;
    int minMax(Board &board, bool isMaximizing);
};

#endif // BOT_H
