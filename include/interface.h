#ifndef INTERFACE_H
#define INTERFACE_H

#include <limits>

class Interface {

public:
    int displayMenu();
    int displayBotMode();
    void displayCredits();
    void goodbye();

private:
    void clearScreen();
};

#endif // INTERFACE_H