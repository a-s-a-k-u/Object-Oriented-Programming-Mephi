
#ifndef LAB3_GOALKEEPER_H
#define LAB3_GOALKEEPER_H
#include "Player.h"
#include "NTP.h"
#include "MS_SS.h"

class Goalkeeper: public DefaultPlayer, public NameTimInTimPen, public MissShotSaveShot {
    size_t total_time = 0;
public:
    Goalkeeper();
    Goalkeeper(std::string &, size_t , size_t , size_t , size_t );
    std::string GetRole() override;
    std::shared_ptr<Player> Creator() override;
    std::string GetInfo() override;
    std::string GetName() override;
    size_t GetTimIn() override;
    size_t GetPenTim() override;

    void SetPenTim(size_t) override;
    void SetMissShoot(size_t) override;
    void SetSaveShoot(size_t) override;
    ~Goalkeeper() override =default;
    void AddTime(size_t time) override {
        total_time += time;
    }

    size_t GetTotalTime() const override {
        return total_time;
    }
};


#endif //LAB3_GOALKEEPER_H