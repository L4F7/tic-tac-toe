#include <iostream>
#include "game.h"
#include "interface.h"

int main() {

    Interface interface;
    Game game;

    while (true){
        int option = interface.displayMenu();
        if (option == 1) game.playerVsPlayer();
        if (option == 2) {
            int mode = interface.displayBotMode();
            if (mode == 3) continue; // If the user goes back to the main menu
            game.playerVsBot(mode);
        };
        if (option == 3) interface.displayCredits();
        if (option == 4){
            interface.goodbye();
            break;
        } 
    }

    return 0;
}