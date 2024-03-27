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
    clearScreen();
    std::cout << "\n      Tic Tac Toe Game\n" << std::endl;
    std::cout << "1. Player vs Player" << std::endl;
    std::cout << "2. Player vs Bot" << std::endl;
    std::cout << "3. Credits" << std::endl;
    std::cout << "4. Exit" << std::endl;
    int choice;
    std::cout << std::endl << "Enter your choice: ";
    std::cin >> choice;
    return  choice;
}

int Interface::displayBotMode() {
    clearScreen();
    std::cout << "\n    Choose Bot Difficulty\n" << std::endl;
    std::cout << "1. Impossible" << std::endl;
    std::cout << "2. Impossible Threaded" << std::endl;
    std::cout << "3. Go back" << std::endl;
    int choice;
    std::cout << std::endl << "Enter your choice: ";
    std::cin >> choice;
    return choice;
}

void Interface::displayCredits() {
    clearScreen();
    std::cout << std::endl << "Developed by: " << std::endl << std::endl;
    std::cout << "  - Luis Fuentes Fuentes" << std::endl;
    std::cout << "  - Andres Gonzalez Romero" << std::endl;
    std::cout << "  - Gerick Vargas Camacho " << std::endl;
    std::cout << std::endl << "Press ENTER to exit";
    std::cin.ignore().get();
}
