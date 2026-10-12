
#ifndef LAB3_SUCS_UNSUCS_H
#define LAB3_SUCS_UNSUCS_H
#include <iostream>

class SucS_UnSucS {
public:
    virtual ~SucS_UnSucS() =default;
    virtual size_t GetSucSh() =0;
    virtual size_t GetUnSucSh() =0;
    virtual void SetSuccessful(size_t) =0;
    virtual void SetUnSuccessful(size_t) =0;
};

class SuccesfulShootUnSuccessfulShoot: public SucS_UnSucS {
protected:
    size_t SuccessfulShots;
    size_t UnsuccessfulShots;
public:
    SuccesfulShootUnSuccessfulShoot();
    size_t GetSucSh() override;
    size_t GetUnSucSh() override;
    void SetSuccessful(size_t) override;
    void SetUnSuccessful(size_t) override;
};


#endif