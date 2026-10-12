#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include "App.h"
#include "Defender.h"
#include "Forward.h"
#include "Goalkeeper.h"
#include <sstream>

TEST_CASE("App Class - Basic Tests", "[App]") {
    App app;

    SECTION("App object can be created") {
        REQUIRE_NOTHROW(App());
    }

    SECTION("GenerateTestTeam creates team") {
        Team team = app.GenerateTestTeam("Test", "Coach", 3, 5);
        REQUIRE(team.GetNameTeam() == "Test");
        REQUIRE(team.GetNameTrainer() == "Coach");
    }
}

TEST_CASE("App Class - QuickTimeTest", "[App][QuickTimeTest]") {
    App app;

    SECTION("QuickTimeTest executes without errors") {
        REQUIRE_NOTHROW(app.QuickTimeTest(50));
    }

    SECTION("QuickTimeTest with different sizes") {
        REQUIRE_NOTHROW(app.QuickTimeTest(0));
        REQUIRE_NOTHROW(app.QuickTimeTest(10));
        REQUIRE_NOTHROW(app.QuickTimeTest(100));
    }
}

TEST_CASE("App Class - Print Methods", "[App][Print]") {
    App app;
    Team team = app.GenerateTestTeam("PrintTest", "Coach", 2, 3);

    SECTION("PrintActivePlayers executes") {
        REQUIRE_NOTHROW(app.PrintActivePlayers(team));
    }

    SECTION("PrintActivePlayersMultithreaded executes") {
        REQUIRE_NOTHROW(app.PrintActivePlayersMultithreaded(team));
    }
}

TEST_CASE("App Class - Team Information", "[App][TeamInfo]") {
    App app;
    TeamList teamList;

    SECTION("GetInformationOfTeam handles empty team list") {
        // Перенаправляем ввод
        auto oldCinBuf = std::cin.rdbuf();
        std::istringstream input("AnyTeam\n");
        std::cin.rdbuf(input.rdbuf());

        std::string result = app.GetInformationOfTeam(teamList);

        std::cin.rdbuf(oldCinBuf);

        REQUIRE(result == "Team not found!");
    }
}

TEST_CASE("App Class - SettingParameters", "[App][Settings]") {
    App app;
    Game game;

    SECTION("SettingParameters with empty game shows message") {
        auto oldCoutBuf = std::cout.rdbuf();
        std::stringstream output;
        std::cout.rdbuf(output.rdbuf());

        auto oldCinBuf = std::cin.rdbuf();
        std::istringstream input("0\n"); // Выбираем 0 (Save and exit)
        std::cin.rdbuf(input.rdbuf());

        game.SetDate("2024-01-01");
        game.SetOpponent("Test");
        game.SetNPlayers(5);

        REQUIRE_NOTHROW(app.SettingParameters(game));

        std::cout.rdbuf(oldCoutBuf);
        std::cin.rdbuf(oldCinBuf);

        REQUIRE_FALSE(output.str().empty());
    }

    SECTION("SettingParameters with uninitialized game") {
        auto oldCoutBuf = std::cout.rdbuf();
        std::stringstream output;
        std::cout.rdbuf(output.rdbuf());

        REQUIRE_NOTHROW(app.SettingParameters(game));

        std::cout.rdbuf(oldCoutBuf);

        REQUIRE(output.str().find("Game is not initialized") != std::string::npos);
    }
}

TEST_CASE("AllPenaltyTimeInGame with Real Player Classes", "[App][Penalty][Real]") {
    App app;
    Game game;


    SECTION("Real Defender penalty") {
        std::string def = "Def1";
        auto defender = std::make_shared<Defender>(def, 90, 7);
        game.AddPlayer(defender);
        game.SetNPlayers(1);

        REQUIRE(app.AllPenaltyTimeInGame(game) == 7);
    }

    SECTION("Real Forward penalty") {
        std::string ref = "Fwd1";
        auto forward = std::make_shared<Forward>(ref, 85, 5, 3, 4);
        game.AddPlayer(forward);
        game.SetNPlayers(1);

        REQUIRE(app.AllPenaltyTimeInGame(game) == 5);
    }

    SECTION("Real Goalkeeper penalty") {
        std::string gl = "Gk1";
        auto keeper = std::make_shared<Goalkeeper>(gl, 95, 3, 2, 8);
        game.AddPlayer(keeper);
        game.SetNPlayers(1);

        REQUIRE(app.AllPenaltyTimeInGame(game) == 3);
    }

    SECTION("Mixed real players") {
        std::string gl = "Gk1";
        std::string def = "Def1";
        std::string ref = "Fwd1";
        auto defender = std::make_shared<Defender>(def, 90, 5);
        auto forward = std::make_shared<Forward>(ref, 85, 3, 2, 4);
        auto keeper = std::make_shared<Goalkeeper>(gl, 95, 2, 1, 8);

        game.AddPlayer(defender);
        game.AddPlayer(forward);
        game.AddPlayer(keeper);
        game.SetNPlayers(3);

        REQUIRE(app.AllPenaltyTimeInGame(game) == 10);
    }
}