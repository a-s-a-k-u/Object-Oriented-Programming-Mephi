#pragma once

#include "Game.h"
#include <string>

class Team {
    std::string trainer, name_team;
    int count_game;
    Vector<Game> Games;
    struct ActivePlayersResult {
        std::shared_ptr<Player> defender;
        std::shared_ptr<Player> forward;
        std::shared_ptr<Player> goalkeeper;
        size_t defender_time;
        size_t forward_time;
        size_t goalkeeper_time;
    };
public:
    Team();
    ~Team() =default;
    Team(const Team& other);
    Team& operator=(const Team& other);
    Team(const std::string&, const std::string& );
    [[nodiscard]] std::string GetNameTeam() const;
    [[nodiscard]] int GetCountGame() const;

    ActivePlayersResult FindAllActivePlayersOptimized(); //single
    ActivePlayersResult FindAllActivePlayersParallel(); //multi

    ActivePlayersResult FindActivePlayersForChunk(size_t start_game, size_t end_game);//sup_multi

    [[nodiscard]] std::string GetNameTrainer() const;
    void Create();
    void Save();
    size_t GetActivePlayerTime(std::string role);
    std::pair<std::shared_ptr<Player>, size_t> GetActivePlayerWithTime(const std::string& role);

    void Clear();

    void AddGame(Game&);
    void DeleteGame(std::string&);

    Game FindGame(const std::string&);
    std::string GetAllGames();
    std::string GetAllPlayers();
    std::shared_ptr<Player> GetActivePlayer(std::string);


    void SetTrainer(std::string tr){trainer = tr;}
    void SetNameTeam(std::string nn){name_team = nn;}


};
