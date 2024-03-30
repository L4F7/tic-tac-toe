#ifndef BOT_H
#define BOT_H

#include <algorithm>
#include <atomic>
#include <functional>
#include <future>
#include <iostream>
#include <thread>
#include <vector>

#include "board.h"
#include "move.h"

class Bot {
    
public:
    void setMode(int mode);
    int getMode();

    Move getBestMove(Board &board);
    Move getBestMoveNonThreaded(Board &board);
    Move getBestMoveThreaded(Board &board);

private:
    int mode = 0;
    int minMax(Board &board, bool isMaximizing);
};

#endif // BOT_H
