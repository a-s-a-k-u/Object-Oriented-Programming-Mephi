//
// Created by lost-mem-ori on 28.11.2025.
//

#include "Forward.h"
#include<format>
Forward::Forward() {
    NamePlayer = "";
    TimeInGame = 0;
    PenaltyTime = 0;
    SuccessfulShots = 0;
    UnsuccessfulShots = 0;
}

Forward::Forward(std::string &name, const size_t time_in, const size_t time_pen, const size_t successful , const size_t unsuccessful)
{
    NamePlayer = name;
    TimeInGame = time_in;
    PenaltyTime = time_pen;
    SuccessfulShots = successful;
    UnsuccessfulShots = unsuccessful;
}


std::string Forward::GetRole() {
    return "Forward";
}

std::string Forward::GetName() {
    return NamePlayer;
}


std::shared_ptr<Player> Forward::Creator() {
    std::string name;
    size_t time_in_game, penalty_time;
    size_t successful_shoot, unsuccessful_shoot;
    std::cout << "Name player: ";
    std::cin >> name;
    std::cout << "Time in game: ";
    std::cin >> time_in_game;
    std::cout << "Penalty time: ";
    std::cin >> penalty_time;
    std::cout << "Successful shoot: ";
    std::cin >> successful_shoot;
    std::cout << "Unsuccessful shoot: ";
    std::cin >> unsuccessful_shoot;
    return std::make_unique<Forward>(name, time_in_game, penalty_time, successful_shoot, unsuccessful_shoot);
}

std::string Forward::GetInfo() {
    std::string line = std::format("{}|{}|{}|{}|{}|{}",
        GetRole() , GetName() , GetTimIn(), GetPenTim(), GetUnSucSh(), GetSucSh());
    return line;
}

size_t Forward::GetTimIn() {
    return TimeInGame;
}

size_t Forward::GetPenTim() {
    return PenaltyTime;
}

void Forward::SetPenTim(size_t pen_time) {
    PenaltyTime = pen_time;
}



