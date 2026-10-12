#include "Team.h"
#include "Game.h"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <format>
#include <unordered_map>
#include <thread>
#include <future>


void Team::AddGame(Game& game) {
    if (game.GetNumPlayers() != 0 || !game.GetDate().empty() || !game.GetOpponent().empty()) {
        Games.push_back(game);
    }
    else {
        std::cout << "Your game is not correct, please checking it" << std::endl;
    }
    count_game++;
}

void Team::Clear() {
    std::for_each(Games.begin(), Games.end(), [](Game& g) {
        g.Clear();
    });
}

void Team::DeleteGame(std::string &date) {

    auto iter = Games.begin();

    while (iter != Games.end()) {
        if (iter->GetDate() == date) {
            auto next = iter;
            ++next;

            auto dest = iter;
            auto src = next;

            while (src != Games.end()) {
                *dest = std::move(*src);
                ++dest;
                ++src;
            }

            Games.pop();

            iter = next - 1;
        }

        if (iter != Games.end()) {
            ++iter;
        }
    }
    count_game--;
}



Game Team::FindGame(const std::string &date) {
    auto i = std::find_if(Games.begin(), Games.end(), [date](Game& gg) {
        return date == gg.GetDate();
    });
    if (i == Games.end()) {
        return Game();
    }
    return *i;
}

std::string Team::GetAllGames() {
    std::string line;
    std::for_each(Games.begin(), Games.end(), [&line](Game& gg){
        line += std::format("Date: {}\n Opponent: {}\n  Count of players: {}\n",
            gg.GetDate(), gg.GetOpponent(), gg.GetNumPlayers());
    });
    return line;
}

std::string Team::GetAllPlayers() {
    std::string line;
    std::for_each(Games.begin(), Games.end(), [&line](Game& gg) {
        line += gg.GetAllPlayers();
    });
    return line;
}

Team::Team() {
    this->trainer = "NN";
    this->name_team = "NN";
    count_game = 0;
}

Team::Team(const Team& other)
    : trainer(other.trainer),
      name_team(other.name_team),
      count_game(other.count_game),
      Games(other.Games) {
}

Team& Team::operator=(const Team& other) {
    if (this != &other) {
        trainer = other.trainer;
        name_team = other.name_team;
        count_game = other.count_game;
        Games = other.Games;
    }
    return *this;
}

Team::Team(const std::string& trainer, const std::string& name) {
    this->trainer = trainer;
    this->name_team = name;
}

void Team::Create() {
    std::string trainer, name_team;
    std::cout << "Name trainer: ";
    std::cin >> trainer;
    std::cout << "Name Team: ";
    std::cin >> name_team;
    this->trainer = trainer;
    this->name_team = name_team;
    std::cout << "Team create!\n";
}


void Team::Save() {
    std::ofstream file;
    file.open("team.txt");
    if (file.is_open()) {
        file << GetNameTeam() << std::endl;
        file << GetAllGames() << std::endl;
    }
    file.close();
}


[[nodiscard]] std::string Team::GetNameTeam() const {
    return name_team;
}
[[nodiscard]] std::string Team::GetNameTrainer() const {
    return trainer;
}


size_t Team::GetActivePlayerTime(std::string role) {
    std::unordered_map<std::string, size_t> total_time_by_name;

    for (size_t i = 0; i < Games.GetSize(); ++i) {
        auto& game = Games[i];

        for (size_t j = 0; j < game.GetPlayers().GetSize(); ++j) {
            auto& player = game.GetPlayers()[j];

            if (player && player->GetRole() == role) {
                std::string name = player->GetName();
                size_t time = player->GetTimIn();
                total_time_by_name[name] += time;
            }
        }
    }

    size_t max_time = 0;

    for (const auto& [name, time] : total_time_by_name) {
        if (time > max_time) {
            max_time = time;
        }
    }

    return max_time;
}
std::pair<std::shared_ptr<Player>, size_t> Team::GetActivePlayerWithTime(const std::string& role) {
    std::unordered_map<std::string, size_t> total_time_by_name;
    std::unordered_map<std::string, std::shared_ptr<Player>> player_by_name;

    for (size_t i = 0; i < Games.GetSize(); ++i) {
        auto& game = Games[i];

        for (size_t j = 0; j < game.GetPlayers().GetSize(); ++j) {
            auto& player = game.GetPlayers()[j];

            if (player && player->GetRole() == role) {
                std::string name = player->GetName();
                size_t time = player->GetTimIn();

                total_time_by_name[name] += time;
                player_by_name[name] = player;
            }
        }
    }

    std::string most_active_name;
    size_t max_time = 0;

    for (const auto& [name, time] : total_time_by_name) {
        if (time > max_time) {
            max_time = time;
            most_active_name = name;
        }
    }

    if (!most_active_name.empty() && player_by_name.find(most_active_name) != player_by_name.end()) {
        return {player_by_name[most_active_name], max_time};
    }

    return {nullptr, 0};
}

std::shared_ptr<Player> Team::GetActivePlayer(std::string role) {
    std::unordered_map<std::string, size_t> total_time_by_name;
    std::unordered_map<std::string, std::shared_ptr<Player>> player_by_name;

    for (auto& game : Games) {
        for (auto& player : game.GetPlayers()) {
            if (player->GetRole() == role) {
                std::string name = player->GetName();
                size_t time = player->GetTimIn();

                total_time_by_name[name] += time;

                player_by_name[name] = player;
            }
        }
    }

    std::string most_active_name;
    size_t max_time = 0;

    for (const auto& [name, time] : total_time_by_name) {
        if (time > max_time) {
            max_time = time;
            most_active_name = name;
        }
    }

    if (!most_active_name.empty()) {
        return player_by_name[most_active_name];
    }

    return nullptr;
}

int Team::GetCountGame() const {
    return count_game;
}

Team::ActivePlayersResult Team::FindAllActivePlayersOptimized() {
    struct PlayerData {
        std::shared_ptr<Player> player;
        size_t total_time = 0;
        std::string role;
    };

    std::unordered_map<std::string, PlayerData> players_data;

    for (size_t i = 0; i < Games.GetSize(); ++i) {
        auto& game = Games[i];

        for (size_t j = 0; j < game.GetPlayers().GetSize(); ++j) {
            auto& player = game.GetPlayers()[j];

            if (!player) continue;

            std::string name = player->GetName();
            std::string role = player->GetRole();
            size_t time = player->GetTimIn();

            if (players_data.find(name) == players_data.end()) {
                players_data[name] = {player, time, role};
            } else {
                players_data[name].total_time += time;
            }
        }
    }

    ActivePlayersResult result;
    size_t max_def_time = 0, max_fwd_time = 0, max_gk_time = 0;

    for (const auto& [name, data] : players_data) {
        if (data.role == "Defender" && data.total_time > max_def_time) {
            max_def_time = data.total_time;
            result.defender = data.player;
            result.defender_time = data.total_time;
        }
        else if (data.role == "Forward" && data.total_time > max_fwd_time) {
            max_fwd_time = data.total_time;
            result.forward = data.player;
            result.forward_time = data.total_time;
        }
        else if (data.role == "Goalkeeper" && data.total_time > max_gk_time) {
            max_gk_time = data.total_time;
            result.goalkeeper = data.player;
            result.goalkeeper_time = data.total_time;
        }
    }

    return result;
}

Team::ActivePlayersResult Team::FindAllActivePlayersParallel() {
    if (Games.GetSize() < 4) {
        return FindAllActivePlayersOptimized();
    }

    unsigned int num_threads = std::thread::hardware_concurrency();
    if (num_threads == 0) num_threads = 2;

    num_threads = std::min(num_threads, static_cast<unsigned int>(Games.GetSize()));

    size_t games_per_thread = Games.GetSize() / num_threads;
    size_t remainder = Games.GetSize() % num_threads;

    Vector<std::future<ActivePlayersResult>> futures;
    size_t start = 0;

    for (unsigned int i = 0; i < num_threads; ++i) {
        size_t end = start + games_per_thread + (i < remainder ? 1 : 0);

        futures.push_back(std::async(std::launch::async,
            [this, start, end]() {
                return FindActivePlayersForChunk(start, end);
            }
        ));

        start = end;
    }

    ActivePlayersResult final_result;
    std::unordered_map<std::string, size_t> total_time_by_name;
    std::unordered_map<std::string, std::shared_ptr<Player>> player_by_name;
    std::unordered_map<std::string, std::string> role_by_name;

    for (auto& future : futures) {
        ActivePlayersResult chunk_result = future.get();

        auto merge_player = [&](const std::shared_ptr<Player>& player, size_t time, const std::string& role) {
            if (!player) return;

            std::string name = player->GetName();

            total_time_by_name[name] += time;


            player_by_name[name] = player;
            role_by_name[name] = role;
        };

        merge_player(chunk_result.defender, chunk_result.defender_time, "Defender");
        merge_player(chunk_result.forward, chunk_result.forward_time, "Forward");
        merge_player(chunk_result.goalkeeper, chunk_result.goalkeeper_time, "Goalkeeper");
    }

    size_t max_def_time = 0, max_fwd_time = 0, max_gk_time = 0;

    for (const auto& [name, time] : total_time_by_name) {
        const std::string& role = role_by_name[name];

        if (role == "Defender" && time > max_def_time) {
            max_def_time = time;
            final_result.defender = player_by_name[name];
            final_result.defender_time = time;
        }
        else if (role == "Forward" && time > max_fwd_time) {
            max_fwd_time = time;
            final_result.forward = player_by_name[name];
            final_result.forward_time = time;
        }
        else if (role == "Goalkeeper" && time > max_gk_time) {
            max_gk_time = time;
            final_result.goalkeeper = player_by_name[name];
            final_result.goalkeeper_time = time;
        }
    }

    return final_result;
}

Team::ActivePlayersResult Team::FindActivePlayersForChunk(size_t start_game, size_t end_game) {
    ActivePlayersResult result;

    std::unordered_map<std::string, std::pair<std::shared_ptr<Player>, size_t>> player_data;
    std::unordered_map<std::string, std::string> player_roles;

    for (size_t i = start_game; i < end_game && i < Games.GetSize(); ++i) {
        auto& game = Games[i];

        for (size_t j = 0; j < game.GetPlayers().GetSize(); ++j) {
            auto& player = game.GetPlayers()[j];

            if (!player) continue;

            std::string name = player->GetName();
            std::string role = player->GetRole();
            size_t time = player->GetTimIn();

            if (player_data.find(name) == player_data.end()) {
                player_data[name] = {player, time};
                player_roles[name] = role;
            } else {
                player_data[name].second += time;
            }
        }
    }


    size_t max_def_time = 0, max_fwd_time = 0, max_gk_time = 0;

    for (const auto& [name, data] : player_data) {
        const std::string& role = player_roles[name];

        if (role == "Defender" && data.second > max_def_time) {
            max_def_time = data.second;
            result.defender = data.first;
            result.defender_time = data.second;
        }
        else if (role == "Forward" && data.second > max_fwd_time) {
            max_fwd_time = data.second;
            result.forward = data.first;
            result.forward_time = data.second;
        }
        else if (role == "Goalkeeper" && data.second > max_gk_time) {
            max_gk_time = data.second;
            result.goalkeeper = data.first;
            result.goalkeeper_time = data.second;
        }
    }

    return result;
}