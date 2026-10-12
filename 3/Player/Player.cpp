#include "Player.h"
#include <format>
#include <iostream>
#include "fstream"

void DefaultPlayer::Save() {
    std::ofstream file;
    file.open("player.txt");
    if (file.is_open()) {
        file << GetInfo();
    }
    file.close();
}

