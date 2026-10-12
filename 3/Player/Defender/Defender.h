
#ifndef LAB3_DEFENDER_H
#define LAB3_DEFENDER_H
#include "Player.h"
#include "NTP.h"

class Defender: public DefaultPlayer, public NameTimInTimPen{
    size_t total_time = 0;
public:
    Defender();
    Defender(std::string &, size_t , size_t );
    std::shared_ptr<Player> Creator() override;
    std::string GetRole() override;
    std::string GetInfo() override;
    std::string GetName() override;
    size_t GetTimIn() override;
    size_t GetPenTim() override;
    void SetPenTim(size_t) override;
    void AddTime(size_t time) override {
        total_time += time;
    }

    size_t GetTotalTime() const override {
        return total_time;
    }
};

#endif //LAB3_DEFENDER_H