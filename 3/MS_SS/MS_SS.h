
#ifndef LAB3_MS_SS_H
#define LAB3_MS_SS_H
#include <iostream>

class MS_SS {
public:
    virtual ~MS_SS() =default;
    virtual size_t GetMsSh() =0;
    virtual size_t GetSvSh() =0;
};

class MissShotSaveShot: public MS_SS {
protected:
    size_t MissedShots;
    size_t SavedShots;
public:
    MissShotSaveShot();
    size_t GetMsSh() override;
    size_t GetSvSh() override;
    virtual void SetMissShoot(size_t) =0;
    virtual void SetSaveShoot(size_t) =0;
};


#endif //LAB3_MS_SS_H