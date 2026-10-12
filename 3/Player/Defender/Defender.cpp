
#include "Defender.h"
#include <iostream>
#include <format>

Defender::Defender() {
    NamePlayer = "";
    TimeInGame = 0;
    PenaltyTime = 0;
}

Defender::Defender(std::string &name, const size_t time_in, const size_t time_pen) {
    NamePlayer = name;
    TimeInGame = time_in;
    PenaltyTime = time_pen;
}


std::string Defender::GetRole(){
    return "Defender";
}

std::string Defender::GetName() {
    return NamePlayer;
}


std::shared_ptr<Player> Defender::Creator() {
    std::string name;
    size_t time_in_game, penalty_time;
    std::cout << "Name player: ";
    std::cin >> name;
    std::cout << "Time in game: ";
    std::cin >> time_in_game;
    std::cout << "Penalty time: ";
    std::cin >> penalty_time;
    return std::make_unique<Defender>(name, time_in_game, penalty_time);
}

std::string Defender::GetInfo() {
    std::string line = std::format("{}|{}|{}|{}",
        GetRole() , GetName() , GetTimIn(), GetPenTim());
    return line;
}
size_t Defender::GetTimIn() {
    return TimeInGame;
}
size_t Defender::GetPenTim() {
    return PenaltyTime;
}

void Defender::SetPenTim(size_t pen_time) {
    PenaltyTime = pen_time;
}

