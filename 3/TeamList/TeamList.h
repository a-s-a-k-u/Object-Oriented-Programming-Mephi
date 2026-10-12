#pragma once
#ifndef LAB3_TEAM_H
#define LAB3_TEAM_H
#include "Team.h"
#include <string>

class TeamList {
    Vector<Team> table;
public:
    TeamList() =default;
    void Save();
    void AddTeam(const Team& game);
    void RemoveTeam(std::string& date);

    Team FindTeam(const std::string &);
    [[nodiscard]] std::string DisplayTeamsTable();

};


#endif //LAB3_TEAM_H