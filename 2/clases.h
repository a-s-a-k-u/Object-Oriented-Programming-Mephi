#ifndef LAB2_CLASES_H
#define LAB2_CLASES_H
#include <iostream>
#include "helpers.h"
class EsCl {
char signal{};
int duration{};

public:
    EsCl() {
        signal = 'X';
        duration = 0;
    }

    EsCl(char &signal, int duration) {
        this->signal = Help::PromtSignal(signal);;
        this->duration = duration;
    }

    EsCl(std::string &line) {
        this->signal = line[0];
        this->duration = line.size();
    }
    void Initialisation (std::string& line);
    void SetSignal(char& sig) {signal = sig;}
    char GetSignal () const {return signal;}
    void SetDuration(int dur){duration = dur;}
    int GetDuration() const {return duration;}

    EsCl& operator+= (int val);
    EsCl& operator-= (int val);
    EsCl& operator ()(EsCl &second, int val);
    friend std::istream &operator>>(std::istream &, EsCl &);
    friend std::ostream &operator<<(std::ostream &, EsCl &);

    int PromtDuration(std::string&) const;
    void EnterOnDisplay(EsCl& ) const;
    void EnterOnDisplay(EsCl& , EsCl&) const;
};

class HrCl {
    EsCl* listsig;
    int capacity;
public:
    HrCl() {
        listsig = new EsCl[0];
        this->capacity = 0;
    }
    HrCl(int capacity) {
        listsig = new EsCl[capacity];
        this->capacity = capacity;
    }
    ~HrCl() {
        delete[] listsig;
    }

    void operator* (int num);
    void operator>> (int num) const;
    void operator<< (int num) const;
    void operator+= (HrCl&);

    EsCl* GetListsig() const {return listsig;}
    void SetListsig(EsCl& list, int signal){listsig[signal] = list;}
    int GetCapacity() const {return this->capacity;}
    void SetCapacity(int newcapacity){this->capacity = newcapacity;}

    void Input();
    void Input(std::string&);
    EsCl* Output(EsCl&);
    void Merge();
    void PrintList();
    void trash();
};

#endif

