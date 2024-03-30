#include <iostream>

#include "interface.h"

void Interface::clearScreen() {
#if defined(_WIN32)
    system("cls");
#elif defined(__linux__)
    system("clear");
#endif
}

int Interface::displayMenu() {
    int choice;
    while(true) {
        clearScreen();
        std::cout << " \n      Tic Tac Toe Game\n\n";
        std::cout << " 1. Player vs Player\n";
        std::cout << " 2. Player vs Bot\n";
        std::cout << " 3. Credits\n";
        std::cout << " 4. Exit\n";
        std::cout << "\n Enter your choice (1-4): ";
        std::cin >> choice; 
        
        if(std::cin.fail())  {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else {
            break;
        }
    }
    return choice;
}

int Interface::displayBotMode() {
    int choice;
    while(true) {
        clearScreen();
        std::cout << " \n    Choose Bot Difficulty\n\n";
        std::cout << " 1. Impossible\n";
        std::cout << " 2. Impossible Threaded\n";
        std::cout << " 3. Go back\n";
        std::cout << "\n Enter your choice (1-3): ";
        std::cin >> choice;
        
        if(std::cin.fail())  {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else {
            break;
        }
    }
    return choice;
}

void Interface::displayCredits() {
    clearScreen();
    std::cout << "\n Developed by: \n\n";
    std::cout << "   - Luis Fuentes Fuentes\n";
    std::cout << "   - Andres Gonzalez Romero\n";
    std::cout << "   - Gerick Vargas Camacho\n";
    std::cout << "\n Press ENTER to go back to the main menu...";
    std::cin.ignore().get();
}

void Interface::goodbye() {
    clearScreen();
    std::cout << "\n    Goodbye. Thank you for playing!\n";
}