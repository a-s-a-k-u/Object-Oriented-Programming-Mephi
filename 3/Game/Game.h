

#ifndef LAB3_GAME_H
#define LAB3_GAME_H
#include "Vector.h"
#include "Player.h"
#include <string>
#include <memory>

class Game {
    std::string date_of_game;
    std::string opponent;
    size_t number_of_players;
    Vector<std::shared_ptr<Player>> players;

public:
    Game();
    std::string GetDate();
    std::string GetOpponent();
    [[nodiscard]] size_t GetNumPlayers() const;

    void SetDate(const std::string& date){date_of_game = date;}
    void SetOpponent(const std::string& oppo){opponent = oppo;}
    void SetNPlayers(const size_t& num){number_of_players = num;}

    [[nodiscard]] std::shared_ptr<Player> SerchPlayerRoleAndActive(std::string) const;


    void AddPlayer(std::shared_ptr<Player>);
    void RemovePlayer(std::string& name);
    std::string GetAllPlayers();

    void Create();
    void Clear();

    Vector<std::shared_ptr<Player>>& GetPlayers() { return players; }
    const Vector<std::shared_ptr<Player>>& GetPlayers() const { return players; }
};


#endif //LAB3_GAME_H