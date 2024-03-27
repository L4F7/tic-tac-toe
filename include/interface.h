#ifndef INTERFACE_H
#define INTERFACE_H

class Interface {
    
public:
    int displayMenu();
    int displayBotMode();
    void displayCredits();

private:
    void clearScreen();

};

#endif // INTERFACE_H