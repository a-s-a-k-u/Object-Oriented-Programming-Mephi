
#include <sstream>

#include "clases.h"
#include "libery_all.h"



void HrCl::Merge() {
    EsCl* opo = new EsCl[capacity];
    int index = 0;
    int len = 0;
    int temp = 0;
    for (int i = 0; i < capacity; i++) {
        if (listsig[i].GetSignal()  == listsig[i+1].GetSignal() ) {
            listsig[i+1].SetDuration(listsig[i].GetDuration() + listsig[i+1].GetDuration());
            continue;
        }
        opo[index] = listsig[i];
        index++;
        len++;
        temp = 0;
    }
    delete[] listsig;
    EsCl* now = new EsCl[len];
    for (int j = 0; j < len; j++) {
        now[j] = opo[j];
    }
    delete[] opo;
    listsig = now;
    capacity = len;
}


void HrCl::Input(std::string& line) {
    int count = 0;
    for (int i = 0; i < line.size(); i++) {
        count++;
        if (line[i] != line[i+1]) {
            EsCl newss(line[i], count);
            if (capacity == 0) {this->listsig[this->capacity] = newss; capacity++;}
            else {
                capacity++;
                EsCl* news = new EsCl[capacity];
                for (int j = 0; j < capacity; j++) {
                    news[j] = listsig[j];
                }
                news[capacity - 1] = newss;
                delete [] this->listsig;
                this->listsig = news;

            }
            count = 0;
        }
    }
}


/*
 *Функция ввода не строкой
*/
void HrCl::Input() {
    EsCl temp;
    std::cin >> temp;
    if (capacity == 0) {listsig[capacity] = temp;}
    else {
        capacity++;
        EsCl* news = new EsCl[capacity];
        for (int i = 0; i < capacity; i++) {
            news[i] = listsig[i];
        }
        news[capacity - 1] = temp;
        delete [] this->listsig;
        this->listsig = news;
        return;
    }
    this->capacity++;
}


void HrCl::PrintList() {
    for (int i = 0; i < capacity; i++)
        std::cout << listsig[i] << ' ';
}
void HrCl::operator*(int num) {
    int oldcap = this->capacity;
    this->capacity = capacity * num;
    EsCl* result = new EsCl[capacity];
    for (int i = 0; i < capacity; i++) {
        for (int j = 0; j < oldcap; j++) {
            result[i] = listsig[j];
            i++;
        }
        i--;
    }
    delete[] listsig;
    listsig = result;
}

void HrCl::operator>> (int num) const{
    for (int i = 0; i < capacity; i++) {
        this->listsig[i].SetDuration(listsig[i].GetDuration() + num);
        if (listsig[i].GetDuration() <= 0) listsig[i].SetDuration(1);
    }
}

void HrCl::operator<< (int num) const {
    for (int i = 0; i < capacity; i++) {
        this->listsig[i].SetDuration(listsig[i].GetDuration() - num);
        if (listsig[i].GetDuration() <= 0) listsig[i].SetDuration(1);
    }
}

void HrCl::operator+=(HrCl& second) {
    int cap = this->capacity + second.capacity;
    EsCl* summ = new EsCl[cap];
    int temp = 0;
    for (int i = 0; i < this->capacity; i++) {
        summ[i] = this->listsig[i];
        temp = i;
    }
    int index = 0;
    for (int j = temp + 1; j < cap; j++) {
        summ[j] = second.listsig[index];
        index++;
    }
    delete[] this->listsig;
    this->listsig = summ;
    this->capacity = cap;
}

void HrCl::trash() {
    this->capacity = 0;
    delete[] this->listsig;
    EsCl* nol = new EsCl[0];
    this->listsig = nol;
}
