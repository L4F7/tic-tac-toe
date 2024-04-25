#ifndef GAME_H
#define GAME_H

#include <chrono>
#include <locale.h>
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

    void start();

private:
    Interface interface;

    void playerVsPlayer();
    void playerVsBot(int mode);
    bool checkWinOrDraw(Board board);
};

#endif // GAME_H