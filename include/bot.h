#ifndef BOT_H
#define BOT_H

#include "board.h"

#include "move.h" 

class Bot {
public:
    Move getBestMove(Board& board);
    Move getBestMoveThreaded(Board& board);

private:
    int minMax(Board& board, bool isMaximizing);
};

#endif // BOT_H
