#ifndef LAB2_HELPERS_H
#define LAB2_HELPERS_H
// #include <iostream>
// #include "libery_all.h"
// #include "clases.h"
class EsCl;
class HrCl;

namespace Help {
    void init();

    void menuEs();
    void menuHr();
    void action(HrCl&, HrCl&, int&);
    void action(EsCl& ,EsCl &, int &);


    char PromtSignal(char &signal);
    void FindErrorCin();
    void PromtClass(EsCl &pop);

    void PrintSignal(EsCl &signal, EsCl &second);

    void ErCin();

}
#endif
