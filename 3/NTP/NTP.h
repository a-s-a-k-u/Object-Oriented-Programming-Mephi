
#ifndef LAB3_NTP_H
#define LAB3_NTP_H
#include <string>

class NTP {
public:
    virtual size_t GetPenTim() =0;
    virtual ~NTP() =default;
};

class NameTimInTimPen: public NTP {
protected:
    std::string NamePlayer;
    size_t TimeInGame;
    size_t PenaltyTime;
public:
    NameTimInTimPen();

    size_t GetPenTim() override;
};

#endif