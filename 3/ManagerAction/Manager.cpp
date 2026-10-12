//
// Created by lost-mem-ori on 26.11.2025.
//

#include "Manager.h"
#include <fstream>
#include <iostream>

Team WriteTeam() {
    std::string date, opponent, trainer, name_team;
    std::cout << "Name team: ";
    std::cin >> name_team;
    std::cout << "Opponents (team vs team): ";
    std::cin >> opponent;
    std::cout << "Data create team (XX.XX.XXXX): ";
    std::cin >> date;
    std::cout << "Trainer: ";
    std::cin >> trainer;
    Team new_team(date, opponent, trainer, name_team);
    return new_team;
}

std::shared_ptr<Player> WritePlayer() {
    std::string Role;
    std::cout << "Who your player?\n" << "Defender/Forward/Goalkeeper\n";
    std::cin >> Role;
    std::shared_ptr<Player> player;
    Defender df;
    Forward fw;
    Goalkeeper gl;
    if ( Role == "Defender") player = df.Creator();
}

std::string Manager::SwitchAction(Team& team, TeamList& team_list) {
    switch (choice) {
        case 1: {
            team = WriteTeam();
            team_list.AddTeam(team);
            break;
        }
        case 2: {
            auto player = WritePlayer();
            break;
        }

        case 3: {
            break;
        }
        case 4: {
            std::cout << Backup(team, team_list) << std::endl;
        }
        default: break;
    }
    return message;
}

std::string Manager::Backup(Team& team, TeamList& team_list) {
    std::ofstream backup;
    backup.open("../team_list.txt");
    if (backup.is_open()) {
        //backup << "Name Team: " << team.GetNameTeam() << '\n';
        backup << team_list.DisplayTeamsTable();
        message = "Successful";
    }
    else message = "BadOpen";
    backup.close();
    return message;
}