//
// Created by lost-mem-ori on 28.11.2025.
//

#include "Goalkeeper.h"
#include <format>
Goalkeeper::Goalkeeper() {
    NamePlayer = "";
    TimeInGame = 0;
    PenaltyTime = 0;
    MissedShots = 0;
    SavedShots = 0;
}

Goalkeeper::Goalkeeper(std::string &name, const size_t ti , const size_t pt, const size_t ms, const size_t ss) {
    NamePlayer = name;
    TimeInGame = ti;
    PenaltyTime = pt;
    MissedShots = ms;
    SavedShots = ss;
}

std::string Goalkeeper::GetRole() {
    return "Goalkeeper";
}


std::shared_ptr<Player> Goalkeeper::Creator() {
    std::string name;
    size_t timeingame, penaltytime;
    size_t missshoot, saveshoot;
    std::cout << "Name player: ";
    std::cin >> name;
    std::cout << "Time in game: ";
    std::cin >> timeingame;
    std::cout << "Penalty time: ";
    std::cin >> penaltytime;
    std::cout << "Missing shoot: ";
    std::cin >> missshoot;
    std::cout << "Saving shoot: ";
    std::cin >> saveshoot;
    return std::make_shared<Goalkeeper>(name, timeingame, penaltytime, missshoot, saveshoot);
}

std::string Goalkeeper::GetInfo() {
    std::string line = std::format("{}|{}|{}|{}|{}|{}",
        GetRole() , GetName() , GetTimIn(), GetPenTim(), GetMsSh(), GetSvSh());
    return line;
}

std::string Goalkeeper::GetName() {
    return NamePlayer;
}



size_t Goalkeeper::GetTimIn() {
    return TimeInGame;
}

size_t Goalkeeper::GetPenTim() {
    return PenaltyTime;
}

void Goalkeeper::SetPenTim(size_t pen_time) {
    PenaltyTime = pen_time;
}

void Goalkeeper::SetMissShoot(size_t miss) {
    MissedShots = miss;
}

void Goalkeeper::SetSaveShoot(size_t save) {
    SavedShots = save;
}

