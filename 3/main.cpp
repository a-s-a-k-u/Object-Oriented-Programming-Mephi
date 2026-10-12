#include "App.h"
#include "Player.h"
#include "Defender.h"
#include "Forward.h"
#include "Goalkeeper.h"
#include <string>
#include <memory>
#include <iostream>

#include "ManagerAction/Manager.h"

class Dialog {
    std::string action;
public:
    Dialog() {
        action = "";
    }
    void menu() const {
        std::ifstream file;
        file.open("Menu.txt", std::ios::binary);
        if (file.is_open()) {
            std::string line;
            while (std::getline(file, line)) {
                if (!line.empty() && line.back() == '\r')
                    line.pop_back();
                std::cerr << line << '\n';
            }
            std::cerr.flush();
        }
        file.close();
    }
    void Chose_Action(int action, Game& game, Team& team, TeamList& team_list, App& app){
        Defender df;
        Forward fw;
        Goalkeeper gl;
        std::shared_ptr<Player> player;
        std::string role;
        std::string date;
        std::string choese;
        int count_game;
          switch(action) {
              case 1: {
                  game.Create();
                  std::cout << "Please write players" << std::endl;
                  for (int i = 0; i < game.GetNumPlayers(); i++) {
                      std::cout << "Write Role player - ";
                      std::cin >> role;
                      if (role == "Defender") {player = df.Creator(); game.AddPlayer(player); continue;}
                      if (role == "Forward") {player = fw.Creator(); game.AddPlayer(player); continue;}
                      if (role == "Goalkeeper") {player = gl.Creator(); game.AddPlayer(player); continue;}
                      std::cout << "Not found this role, please write Defender/Forward/Goalkeeper" << std::endl;
                      i--;
                  }
                  std::cout <<game.GetAllPlayers() << std::endl;
                  if (team.GetCountGame() != 0) {
                      std::cout << "Add to team: " << team.GetNameTeam() << "?(yes/no)\n";
                      std::cin >> choese;
                      if (choese == "yes") {
                          team.AddGame(game);
                          game.Clear();
                      }
                  }
                  break;
              }
              case 2: {
                  std::cout << "\tCreate Team!" << std::endl;
                  team.Create();
                  team.AddGame(game);
                  std::cout << "Successful add game into team" <<std::endl;
                  game.Clear();
                  break;
              }
              case 3: {
                  team_list.AddTeam(team);
                  team.Clear();
                  break;
              }
              case 4: {
                  break;
              }
              case 6: {
                  std::cout << "Date: ";
                  std::cin >> date;
                  team.DeleteGame(date);
                  break;
              }
              case 7: {
                  std::cout << app.AllPenaltyTimeInGame(game) << std::endl;
                  break;
              }
              case 8: {
                  std::cout << app.GetInformationOfTeam(team_list) << std::endl;
                  break;
              }
              case 9: {
                  std::cout << "Name team: ";
                  std::string name;
                  std::cin >> name;
                  Team teaaam = team_list.FindTeam(name);

                  std::cout << "DEBUG: Team found: " << teaaam.GetNameTeam()
                            << ", Trainer: " << teaaam.GetNameTrainer() << std::endl;

                  if (teaaam.GetNameTeam() != "NN") {
                      std::cout << "\nMost active players:\n";
                      app.PrintActivePlayersMultithreaded(teaaam);
                  } else {
                      std::cout << "Team not found!\n";
                  }
                  break;

              }
              case 10: {
                  std::cout << "Count test game" << std::endl;
                  std::cin >> count_game;
                  app.QuickTimeTest(count_game);
                  break;
              }

          }
    }
};

static_assert(std::random_access_iterator<Vector<int>::Iterator>);
static_assert(std::random_access_iterator<Vector<double>::Iterator>);


int main() {
    Game game;
    Team team;
    TeamList team_list;
    Dialog dd;
    App app;
    int action{};

    while (action != 4) {
        dd.menu();
        std::cin >> action;
        dd.Chose_Action(action, game, team, team_list, app);
    }
    return 0;
}