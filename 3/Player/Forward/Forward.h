

#ifndef LAB3_FORWARD_H
#define LAB3_FORWARD_H
#include "Player.h"
#include "NTP.h"
#include "SucS_UnSucS.h"

class Forward: public DefaultPlayer, public NameTimInTimPen, public SuccesfulShootUnSuccessfulShoot{
    size_t total_time = 0;
public:
    Forward();
    Forward(std::string &, size_t , size_t , size_t , size_t );
    std::shared_ptr<Player> Creator() override;
    std::string GetRole() override;
    std::string GetInfo() override;
    std::string GetName() override;
    size_t GetTimIn() override;
    size_t GetPenTim() override;
    void SetPenTim(size_t pen_time) override;
    void AddTime(size_t time) override {
        total_time += time;
    }

    size_t GetTotalTime() const override {
        return total_time;
    }
};


#endif //LAB3_FORWARD_H