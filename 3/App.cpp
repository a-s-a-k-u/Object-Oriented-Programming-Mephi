

#include "App.h"
#include <string>
#include <sstream>
#include <format>
#include <thread>
#include <future>
#include <chrono>
#include <random>
#include <iomanip>
#include <fstream>

#include "Goalkeeper.h"
#include "Forward.h"
#include "Defender.h"


Team App::GenerateTestTeam(const std::string& team_name, const std::string& trainer_name,
                           int game_count, int players_per_game) {
    Team team;
    team.SetTrainer(trainer_name);
    team.SetNameTeam(team_name);

    static std::mt19937 rng(std::random_device{}());
    static std::uniform_int_distribution<size_t> time_dist(1, 120);
    static std::uniform_int_distribution<size_t> penalty_dist(0, 20);
    static std::uniform_int_distribution<size_t> shots_dist(0, 10);

    Vector<std::string> names;
    names.push_back("Ivanov");
    names.push_back("Petrov");
    names.push_back("Sidorov");
    names.push_back("Kuznetsov");
    names.push_back("Smirnov");
    names.push_back("Popov");
    names.push_back("Volkov");
    names.push_back("Lebedev");
    names.push_back("Kozlov");
    names.push_back("Novikov");

    Vector<std::string> roles;
    roles.push_back("Defender");
    roles.push_back("Forward");
    roles.push_back("Goalkeeper");

    for (int game_idx = 0; game_idx < game_count; ++game_idx) {
        Game game;
        game.SetDate("2024-01-" + std::to_string(game_idx + 1));
        game.SetOpponent("Opponent_" + std::to_string(game_idx));
        game.SetNPlayers(players_per_game);

        for (int player_idx = 0; player_idx < players_per_game; ++player_idx) {
            std::string name = names[rng() % names.GetSize()] + "_" + std::to_string(player_idx);
            std::string role = roles[rng() % roles.GetSize()];
            size_t time_in_game = time_dist(rng);
            size_t penalty_time = penalty_dist(rng);

            std::shared_ptr<Player> player;

            if (role == "Defender") {
                player = std::make_shared<Defender>(name, time_in_game, penalty_time);
            }
            else if (role == "Forward") {
                size_t successful = shots_dist(rng);
                size_t unsuccessful = shots_dist(rng);
                player = std::make_shared<Forward>(name, time_in_game, penalty_time, successful, unsuccessful);
            }
            else if (role == "Goalkeeper") {
                size_t saved = shots_dist(rng);
                size_t missed = shots_dist(rng);
                player = std::make_shared<Goalkeeper>(name, time_in_game, penalty_time, missed, saved);
            }

            if (player) {
                game.AddPlayer(player);
            }
        }

        team.AddGame(game);
    }

    return team;
}

void App::QuickTimeTest(int cout_game) {

    Team team;
    team.SetTrainer("Test");
    team.SetNameTeam("Test");

    std::mt19937 rng(456);

    for (int g = 0; g < cout_game; g++) {
        Game game;
        game.SetDate("2024-01-01");
        game.SetOpponent("Opp");
        game.SetNPlayers(10);

        for (int p = 0; p < 10; p++) {
            std::string name = "P" + std::to_string(p);
            size_t time = 30 + rng() % 90;

            if (p % 3 == 0) {
                auto player = std::make_shared<Defender>(name, time, rng() % 10);
                game.AddPlayer(player);
            }
            else if (p % 3 == 1) {
                auto player = std::make_shared<Forward>(name, time, rng() % 10, rng() % 5, rng() % 5);
                game.AddPlayer(player);
            }
            else {
                auto player = std::make_shared<Goalkeeper>(name, time, rng() % 10, rng() % 5, rng() % 5);
                game.AddPlayer(player);
            }
        }

        team.AddGame(game);
    }


    auto t1 = std::chrono::high_resolution_clock::now();


    for (int i = 0; i < 50; i++) {
        team.FindAllActivePlayersOptimized();
    }

    auto t2 = std::chrono::high_resolution_clock::now();


    for (int i = 0; i < 50; i++) {
        auto d = std::async([&]() { return team.FindAllActivePlayersParallel();});
        d.get();
    }

    auto t3 = std::chrono::high_resolution_clock::now();

    double single = std::chrono::duration<double, std::milli>(t2 - t1).count();
    double multi = std::chrono::duration<double, std::milli>(t3 - t2).count();

    std::cout << single << " ms (single)\n";
    std::cout << multi << " ms (multi)\n";
    std::cout << "Ratio: " << single/multi << "\n";
}


void App::PrintActivePlayers(Team& team) {
    auto start_time = std::chrono::high_resolution_clock::now();
    std::cout << "\n=== Most Active Players ===\n";

    auto defender = team.GetActivePlayer("Defender");
    if (defender) {
        size_t defender_time = team.GetActivePlayerTime("Defender");
        std::cout << defender->GetRole() << "\t"
                  << defender->GetName() << "\t"
                  << "Total time: " << defender_time << " minutes\n";
    } else {
        std::cout << "Defender\tNo players found\n";
    }

    auto forward = team.GetActivePlayer("Forward");
    if (forward) {
        size_t forward_time = team.GetActivePlayerTime("Forward");
        std::cout << forward->GetRole() << "\t"
                  << forward->GetName() << "\t"
                  << "Total time: " << forward_time << " minutes\n";
    } else {
        std::cout << "Forward\tNo players found\n";
    }

    auto goalkeeper = team.GetActivePlayer("Goalkeeper");
    if (goalkeeper) {
        size_t goalkeeper_time = team.GetActivePlayerTime("Goalkeeper");
        std::cout << goalkeeper->GetRole() << "\t"
                  << goalkeeper->GetName() << "\t"
                  << "Total time: " << goalkeeper_time << " minutes\n";
    } else {
        std::cout << "Goalkeeper\tNo players found\n";
    }
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);

    std::cout << "\n  Execution time: " << duration.count() << " microseconds\n";
    std::cout << "==========================\n";
}

int App::AllPenaltyTimeInGame(Game &game) {
    int value{};
    std::string line = game.GetAllPlayers();
    std::istringstream lol(line);
    std::string cr;
    int count = 0;
    while (std::getline(lol,cr,'\n')) {
        std::istringstream rtr(cr);
        std::string lin;
        while (std::getline(rtr, lin, '|')) {
            count++;
            if (count == 4) {value += std::stoi(lin); count = 0;}
        }
    }
    return value;
}

std::string App::GetInformationOfTeam(TeamList& team_list) {
    std::string line;
    std::cout << "Write name team that you searching: ";
    std::cin >> line;

    Team t = team_list.FindTeam(line);

    if (t.GetNameTeam() == "NN" && t.GetNameTrainer() == "NN") {
        return "Team not found!";
    }

    return std::format("Team: {}\nTrainer: {}\nPlayers:\n{}",
                      t.GetNameTeam(), t.GetNameTrainer(), t.GetAllPlayers());
}



void App::PrintActivePlayersMultithreaded(Team& team) {
    auto start_time = std::chrono::high_resolution_clock::now();
    std::cout << "\n=== Most Active Players (Multithreaded) ===\n";

    Vector<std::string> roles;
    roles.push_back("Defender");
    roles.push_back("Forward");
    roles.push_back("Goalkeeper");
    Vector<std::future<std::pair<std::shared_ptr<Player>, size_t>>> futures;

    for (const auto& role : roles) {
        futures.push_back(std::async(std::launch::async, [&team, role]() {
            return team.GetActivePlayerWithTime(role);
        }));
    }

    for (size_t i = 0; i < roles.GetSize(); ++i) {
        try {
            auto [player, time] = futures[i].get();
            if (player) {
                std::cout << roles[i] << "\t"
                          << player->GetName() << "\t"
                          << "Total time: " << time << " minutes\n";
            } else {
                std::cout << roles[i] << "\tNo players found\n";
            }
        } catch (const std::exception& e) {
            std::cout << roles[i] << "\tError: " << e.what() << "\n";
        }
    }
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);

    std::cout << "\n  Execution time: " << duration.count() << " microseconds\n";
    std::cout << "===========================================\n";
}

void App::SettingParameters(Game& game) {
    if (game.GetDate().empty()) {
        std::cout << "Game is not initialized. Please create game first.\n";
        return;
    }

    int choice;
    do {
        std::cout << "\n=== Game Parameters Configuration ===\n";
        std::cout << "Current game: " << game.GetDate() << " vs " << game.GetOpponent() << "\n";
        std::cout << "Players: " << game.GetNumPlayers() << "\n";
        std::cout << "\nSelect parameter to modify:\n";
        std::cout << "1. Change date\n";
        std::cout << "2. Change opponent\n";
        std::cout << "3. Change number of players\n";
        std::cout << "4. Edit specific player\n";
        std::cout << "5. Add new player\n";
        std::cout << "6. Remove player\n";
        std::cout << "7. Recalculate player statistics\n";
        std::cout << "8. Adjust game constraints\n";
        std::cout << "9. View current parameters\n";
        std::cout << "0. Save and exit\n";
        std::cout << "Choice: ";

        std::cin >> choice;

        switch(choice) {
            case 1: {
                std::string new_date;
                std::cout << "Current date: " << game.GetDate() << "\n";
                std::cout << "New date (YYYY-MM-DD): ";
                std::cin >> new_date;
                game.SetDate(new_date);
                std::cout << "Date updated.\n";
                break;
            }
            case 2: {
                std::string new_opponent;
                std::cout << "Current opponent: " << game.GetOpponent() << "\n";
                std::cout << "New opponent: ";
                std::cin.ignore();
                std::getline(std::cin, new_opponent);
                game.SetOpponent(new_opponent);
                std::cout << "Opponent updated.\n";
                break;
            }
            case 3: {
                int new_count;
                std::cout << "Current player count: " << game.GetNumPlayers() << "\n";
                std::cout << "New player count: ";
                std::cin >> new_count;

                if (new_count < 0) {
                    std::cout << "Invalid number!\n";
                } else if (new_count < game.GetNumPlayers()) {
                    std::cout << "Warning: New count is less than current. Some players will be removed.\n";
                    std::cout << "Confirm? (y/n): ";
                    char confirm;
                    std::cin >> confirm;
                    if (confirm == 'y' || confirm == 'Y') {
                        game.SetNPlayers(new_count);
                    }
                } else {
                    game.SetNPlayers(new_count);
                }
                break;
            }
            case 4: {
                // Edit specific player
                std::cout << "\nCurrent players:\n";
                auto players = game.GetPlayers();

                if (players.GetSize() == 0) {
                    std::cout << "No players in game.\n";
                    break;
                }

                for (size_t i = 0; i < players.GetSize(); ++i) {
                    if (players[i]) {
                        std::cout << i+1 << ". " << players[i]->GetName()
                                  << " [" << players[i]->GetRole() << "]\n";
                    }
                }

                std::cout << "Select player to edit (1-" << players.GetSize() << "): ";
                int player_idx;
                std::cin >> player_idx;

                if (player_idx < 1 || player_idx > static_cast<int>(players.GetSize())) {
                    std::cout << "Invalid selection.\n";
                    break;
                }

                auto& player = players[player_idx - 1];
                if (!player) break;

                std::cout << "\nEditing " << player->GetName() << " (" << player->GetRole() << ")\n";
                std::cout << "1. Change name\n";
                std::cout << "2. Adjust playing time\n";
                std::cout << "3. Adjust penalty time\n";

                if (auto defender = std::dynamic_pointer_cast<Defender>(player)) {
                    std::cout << "4. Defender specific stats\n";
                } else if (auto forward = std::dynamic_pointer_cast<Forward>(player)) {
                    std::cout << "4. Adjust shots (successful/unsuccessful)\n";
                } else if (auto keeper = std::dynamic_pointer_cast<Goalkeeper>(player)) {
                    std::cout << "4. Adjust saves/misses\n";
                }

                std::cout << "Choice: ";
                int player_choice;
                std::cin >> player_choice;

                switch(player_choice) {
                    case 1: {
                        std::string new_name;
                        std::cout << "New name: ";
                        std::cin >> new_name;
                        break;
                    }
                    case 2: {
                        size_t new_time;
                        std::cout << "Current time: " << player->GetTimIn() << "\n";
                        std::cout << "New playing time (minutes): ";
                        std::cin >> new_time;
                        break;
                    }
                    case 3: {
                        size_t new_penalty;
                        std::cout << "Current penalty: " << player->GetPenTim() << "\n";
                        std::cout << "New penalty time (minutes): ";
                        std::cin >> new_penalty;
                        player->SetPenTim(new_penalty);
                        break;
                    }
                    case 4: {
                        if (auto forward = std::dynamic_pointer_cast<Forward>(player)) {
                            size_t successful, unsuccessful;
                            std::cout << "Current successful shots: " << forward->GetSucSh() << "\n";
                            std::cout << "New successful shots: ";
                            std::cin >> successful;
                            std::cout << "Current unsuccessful shots: " << forward->GetUnSucSh() << "\n";
                            std::cout << "New unsuccessful shots: ";
                            std::cin >> unsuccessful;
                            forward->SetSuccessful(successful);
                            forward->SetUnSuccessful(unsuccessful);
                        } else if (auto keeper = std::dynamic_pointer_cast<Goalkeeper>(player)) {
                            size_t missed, saved;
                            std::cout << "Current missed goals: " << keeper->GetMsSh() << "\n";
                            std::cout << "New missed goals: ";
                            std::cin >> missed;
                            std::cout << "Current saved goals: " << keeper->GetSvSh() << "\n";
                            std::cout << "New saved goals: ";
                            std::cin >> saved;
                            keeper->SetMissShoot(missed);
                            keeper->SetSaveShoot(saved);
                        }
                        break;
                    }
                }
                break;
            }
            case 5: {
                std::cout << "\nAdd new player:\n";
                std::cout << "Role (Defender/Forward/Goalkeeper): ";
                std::string role;
                std::cin >> role;

                std::shared_ptr<Player> new_player;

                if (role == "Defender") {
                    std::string name;
                    size_t time, penalty;
                    std::cout << "Name: "; std::cin >> name;
                    std::cout << "Playing time: "; std::cin >> time;
                    std::cout << "Penalty time: "; std::cin >> penalty;
                    new_player = std::make_shared<Defender>(name, time, penalty);
                }
                else if (role == "Forward") {
                    std::string name;
                    size_t time, penalty, successful, unsuccessful;
                    std::cout << "Name: "; std::cin >> name;
                    std::cout << "Playing time: "; std::cin >> time;
                    std::cout << "Penalty time: "; std::cin >> penalty;
                    std::cout << "Successful shots: "; std::cin >> successful;
                    std::cout << "Unsuccessful shots: "; std::cin >> unsuccessful;
                    new_player = std::make_shared<Forward>(name, time, penalty, successful, unsuccessful);
                }
                else if (role == "Goalkeeper") {
                    std::string name;
                    size_t time, penalty, missed, saved;
                    std::cout << "Name: "; std::cin >> name;
                    std::cout << "Playing time: "; std::cin >> time;
                    std::cout << "Penalty time: "; std::cin >> penalty;
                    std::cout << "Missed goals: "; std::cin >> missed;
                    std::cout << "Saved goals: "; std::cin >> saved;
                    new_player = std::make_shared<Goalkeeper>(name, time, penalty, missed, saved);
                }
                else {
                    std::cout << "Invalid role!\n";
                    break;
                }

                game.AddPlayer(new_player);
                std::cout << "Player added.\n";
                break;
            }
            case 6: {
                auto players = game.GetPlayers();
                if (players.GetSize() == 0) {
                    std::cout << "No players to remove.\n";
                    break;
                }

                std::cout << "\nSelect player to remove:\n";
                for (size_t i = 0; i < players.GetSize(); ++i) {
                    if (players[i]) {
                        std::cout << i+1 << ". " << players[i]->GetName()
                                  << " [" << players[i]->GetRole() << "]\n";
                    }
                }

                std::cout << "Choice (0 to cancel): ";
                int remove_idx;
                std::cin >> remove_idx;

                if (remove_idx > 0 && remove_idx <= static_cast<int>(players.GetSize())) {
                    std::cout << "Remove " << players[remove_idx-1]->GetName() << "? (y/n): ";
                    char confirm;
                    std::cin >> confirm;
                    if (confirm == 'y' || confirm == 'Y') {
                        // Нужно добавить метод RemovePlayer в Game
                        // game.RemovePlayer(remove_idx-1);
                        std::cout << "Player removed.\n";
                    }
                }
                break;
            }
            case 7: {
                std::cout << "\nRecalculating statistics...\n";
                int total_penalty = AllPenaltyTimeInGame(game);
                std::cout << "Total penalty time: " << total_penalty << " minutes\n";

                auto players = game.GetPlayers();
                size_t total_time = 0;
                for (const auto& player : players) {
                    if (player) total_time += player->GetTimIn();
                }
                std::cout << "Total playing time: " << total_time << " minutes\n";

                int defenders = 0, forwards = 0, goalkeepers = 0;
                for (const auto& player : players) {
                    if (!player) continue;
                    std::string role = player->GetRole();
                    if (role == "Defender") defenders++;
                    else if (role == "Forward") forwards++;
                    else if (role == "Goalkeeper") goalkeepers++;
                }

                std::cout << "Role distribution:\n";
                std::cout << "  Defenders: " << defenders << "\n";
                std::cout << "  Forwards: " << forwards << "\n";
                std::cout << "  Goalkeepers: " << goalkeepers << "\n";
                break;
            }
            case 8: {
                std::cout << "\nGame Constraints:\n";
                std::cout << "1. Set maximum players per role\n";
                std::cout << "2. Set minimum playing time\n";
                std::cout << "3. Set maximum penalty time\n";
                std::cout << "Choice: ";

                int constraint_choice;
                std::cin >> constraint_choice;

                std::cout << "Constraint functionality to be implemented.\n";
                break;
            }
            case 9: {
                std::cout << "\n=== Game Parameters Summary ===\n";
                std::cout << "Date: " << game.GetDate() << "\n";
                std::cout << "Opponent: " << game.GetOpponent() << "\n";
                std::cout << "Number of players: " << game.GetNumPlayers() << "\n";
                std::cout << "\nPlayers:\n";
                std::cout << game.GetAllPlayers() << "\n";

                std::cout << "\nStatistics:\n";
                std::cout << "Total penalty time: " << AllPenaltyTimeInGame(game) << "\n";
                break;
            }
            case 0: {
                std::cout << "Changes saved.\n";
                break;
            }
            default: {
                std::cout << "Invalid choice.\n";
                break;
            }
        }

        if (choice != 0) {
            std::cout << "\nPress Enter to continue...";
            std::cin.ignore();
            std::cin.get();
        }

    } while (choice != 0);
}