#ifndef GAME_H
#define GAME_H

#include <chrono>
#include <locale.h>
#include <utility> // for std::pair
#include <vector>

#include "board.h"
#include "bot.h"
#include "fileManager.h"
#include "interface.h"
#include "move.h"

class Game {

public:
    Game();
    ~Game();

    Interface getInterface();
    void setInterface(Interface interface);

    void start();

private:
    Interface interface;
    FileManager fileManager;

    void initNcurses();
    void endNcurses();
    void runMainMenu();
    void runBotMenu();
    void runSimulateGamesMenu();
    void playerVsPlayer();
    void playerVsBot(int mode);
    void botVsBot(int mode);
    void saveExecutionTimes(std::vector<std::pair<int, int>> executionTimes);
    void simulateGames(int games, int mode);
};

#endif // GAME_H