

#include "TeamList.h"
#include <algorithm>
#include <fstream>

void TeamList::AddTeam(const Team &team) {
    table.push_back(team);
}


std::string TeamList::DisplayTeamsTable(){
    std::string line;
    std::for_each(table.begin(), table.end(), [&line](Team& r) {
        line += r.GetNameTeam() + r.GetAllGames();
    });
    return line;
}

void TeamList::RemoveTeam(std::string& date) {
    std::for_each(table.begin(), table.end(), [&date](Team& team) {
        team.DeleteGame(date);
    });
}



Team TeamList::FindTeam(const std::string& name) {
    std::cout << "DEBUG: Searching for team: " << name << std::endl;
    std::cout << "DEBUG: Number of teams: " << table.GetSize() << std::endl;

    for (size_t i = 0; i < table.GetSize(); ++i) {
        std::cout << "DEBUG: Team " << i << ": " << table[i].GetNameTeam() << std::endl;
        if (table[i].GetNameTeam() == name) {
            std::cout << "DEBUG: Found team!" << std::endl;

            return Team(table[i]);
        }
    }

    std::cout << "DEBUG: Team not found, returning default" << std::endl;
    return Team();
}

void TeamList::Save() {
    std::ofstream file;
    file.open("teamlist.txt");
    if (file.is_open()) {
        std::for_each(table.begin(), table.end(), [&file](Team& x) {
            file << x.GetNameTeam() << std::endl;
            file << x.GetAllGames() << std::endl;
            file << x.GetAllPlayers() << std::endl;
        });
    }
    file.close();
}