

#include "Game.h"
#include <iostream>
#include <algorithm>
#include <format>


void Game::Clear() {
    SetDate("");
    SetNPlayers(0);
    SetOpponent("");
    while (!players.empty()) {
        players.pop();
    }
}

Game::Game() {
    date_of_game = "";
    opponent = "";
    number_of_players = 0;
}

void Game::Create() {
    if (!players.empty()) {
        while (players.GetSize() != 0) players.pop();
    }
    std::cout << "Date: ";
    std::cin >> date_of_game;
    std::cout << "Opponent: ";
    std::cin >> opponent;
    std::cout << "Number of players: ";
    std::cin >> number_of_players;
    std::cout << "Successful create!\n";
}

std::string Game::GetAllPlayers() {
    std::string line;
    std::for_each(players.begin(), players.end(), [&line](std::shared_ptr<Player>& player) {
        line += player->GetInfo() + '\n';
    });
    return line;
}

std::string Game::GetDate() {
    return date_of_game;
}

std::string Game::GetOpponent() {
    return opponent;
}

size_t Game::GetNumPlayers() const{
    return number_of_players;
}

void Game::AddPlayer(std::shared_ptr<Player> player) {
    if (number_of_players <= 10) { players.push_back(player);  return;}
    if (number_of_players < 10 + 5) {
        players.push_back(player);
        std::cout << "He is substitute player" << std::endl;
    }
}

void Game::RemovePlayer(std::string &name) {
    int index = 0;
    for (; index < players.GetSize(); index++) {
        if (players[index]->GetName() == name) break;
    }
    for (int i = index; i < players.GetSize() - 1; i++) {
        players[i] = players[i+1];
    }
    players.pop();
}

std::shared_ptr<Player> Game::SerchPlayerRoleAndActive(std::string role) const {
    std::shared_ptr<Player> active_player = nullptr;
    size_t max_time = 0;

    for (const auto& player : players) {
        if (player->GetRole() == role) {
            size_t time = player->GetTimIn();
            if (time > max_time) {
                max_time = time;
                active_player = player;
            }
        }
    }
    return active_player;
}





