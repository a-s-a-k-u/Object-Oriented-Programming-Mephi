//
// Created by lost-mem-ori on 26.11.2025.
//
#pragma once
#include "../Customize/MenuChoice.h"
#include "../TeamList/TeamList.h"
#include "../Team/Team.h"


#ifndef LAB3_MANAGER_H
#define LAB3_MANAGER_H


class Manager: public MenuChoice{
    std::string massage;
public:
    ~Manager()override =default;

    std::string SwitchAction (Team&, TeamList&);

    std::string Backup(Team&, TeamList&);
};


#endif //LAB3_MANAGER_H