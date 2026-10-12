

#ifndef LAB3_APP_H
#define LAB3_APP_H

#include "TeamList.h"
#include <string>

class App {
public:
    /**
     * @brief Функция вычисления штрафного времени всей команды в конкретной игре
     * @return вычисленное число
     */
    int AllPenaltyTimeInGame(Game& );


    /**
     * @brief Функция представления краткой информации команды с ролями
     * @return строку информации
     */
    std::string GetInformationOfTeam(TeamList& );

    /**
     * @brief Фунция тонкой настройки определенной игры
     */
    void SettingParameters(Game& );

	/**
	* @brief Функция для получения самых активных игроков
	*/
	void PrintActivePlayers(Team&);

	void PrintActivePlayersMultithreaded(Team& team);

	Team GenerateTestTeam(const std::string& team_name, const std::string& trainer_name,
					  int game_count, int players_per_game);

	void QuickTimeTest(int);
};


#endif //LAB3_APP_H