//
// Created by lost-mem-ori on 26.11.2025.
//

#ifndef LAB3_MENUCHOICE_H
#define LAB3_MENUCHOICE_H

#include <string>

class MenuChoice {
protected:
    int choice;
    std::string message;
public:
    virtual ~MenuChoice() = default;

    MenuChoice() {
        choice = 0;
        message = "";
    }
    void PrintMenu() const;
    int ChoiceAction();
    //virtual std::string SwitchAction () =0;
};


#endif //LAB3_MENUCHOICE_H