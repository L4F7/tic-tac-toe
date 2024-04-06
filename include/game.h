#ifndef GAME_H
#define GAME_H

#include <chrono>
#include <iomanip>
#include <thread>
#include <vector>

#include "board.h"
#include "bot.h"
#include "interface.h"

class Game {

public:
    Game();
    ~Game();


    Interface getInterface();
    void setInterface(Interface interface);

    Board getBoard();
    void setBoard(Board board);

    void start();
    void playerVsPlayer();
    void playerVsBot(int mode);

private:
    bool checkWinOrDraw(Board board);
    Interface interface;
    Board board;
};

#endif // GAME_H