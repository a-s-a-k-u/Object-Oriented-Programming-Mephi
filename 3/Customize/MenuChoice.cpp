//
// Created by lost-mem-ori on 26.11.2025.
//

#include "MenuChoice.h"
#include <iostream>
#include <limits>

void MenuChoice::PrintMenu() const{
    std::cout << "----Menu----\n"
    << "1 - New team\n"
    << "2 - Add player into team\n"
    << "3 - Create game\n"
    << "4 - Exit and backup\n"
    << "------------\n";
}

int MenuChoice::ChoiceAction() {
    std::cout << "Write choice: ";
    while (true) {
        std::cin >> choice;
        if (choice > 4 || choice < 1) {
            std::cout << "This have not in menu\nPlease again\n";
            std::cin.clear();
            std::cin.ignore(std::streamsize(std::max<int>), '\n');
            continue;
        }
        break;
    }
    return choice;
}