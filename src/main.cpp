#include <iostream>
#include "game.h"
#include "interface.h"

int main() {

    while (true){
        Interface interface;
        Game game;
        int option = interface.displayMenu();
        if (option == 1) game.playerVsPlayer();
        if (option == 2) game.playerVsBot(interface.displayBotMode());
        if (option == 3) interface.displayCredits();
        if (option == 4) break;
    }

    return 0;
}