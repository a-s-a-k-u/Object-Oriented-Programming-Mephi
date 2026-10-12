#pragma once
#include <string>
#include <memory>

#ifndef LAB3_PLAYER_H
#define LAB3_PLAYER_H

class Player {
public:
    virtual ~Player() =default;
    virtual std::string GetInfo() =0;
    virtual void Save() =0;
    virtual std::string GetName() =0;
    virtual std::string GetRole() =0;

    virtual void AddTime(size_t time) = 0;
    virtual size_t GetTotalTime() const = 0;

    virtual size_t GetTimIn() =0;
    virtual size_t GetPenTim() =0;

    virtual void SetPenTim(size_t) =0;
};

class DefaultPlayer: public Player {
public:
    virtual std::shared_ptr<Player> Creator() =0;
    std::string GetRole() override =0;
    std::string GetInfo() override =0;
    std::string GetName() override =0;
    size_t GetTimIn() override =0;
    size_t GetPenTim() override =0;
    void Save() override;
};


#endif //LAB3_PLAYER_H