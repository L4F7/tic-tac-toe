#ifndef GAME_H
#define GAME_H

#include <chrono>
#include <vector>

#include "board.h"
#include "bot.h"

class Game {

    public: 
        void playerVsPlayer();
        void playerVsBot(int mode);

    private:
        bool checkWinOrDraw(Board board);
    
};

#endif // GAME_H