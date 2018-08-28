/*
** EPITECH PROJECT, 2018
** Core
** File description:
** Declaration of Data
*/

#ifndef PSU_ZAPPY_2017_DATA_HPP
#define PSU_ZAPPY_2017_DATA_HPP

#include <algorithm>

#include "Map.hpp"
#include "Bot.hpp"
#include "Egg.hpp"
#include "Utils.hpp"

class Data {
public:
	Data();

	std::string extractMessage(const std::vector<std::string> &args,
	                           unsigned int n);
	void destroyDeadBots();
	void destroyDeadEggs();
	void addTeamName(const std::string &name);
	void removeTeamName(const std::string &name);
	bool doesTeamNameExists(const std::string &name) const;
	void printTeamNames();
	void printBots();
	void printEggs();

	void checkPos(const std::string &cmd, const pos_t &pos);
	void checkResourceId(const std::string &cmd, unsigned int id);
	void checkArgNumber(const std::string &cmd, unsigned int argsSize,
	                    unsigned int expectedSize);
	void checkArgAtLeastNumber(const std::string &cmd, unsigned int argsSize,
	                    unsigned int expectedSize);
	void checkInitializedMap(const std::string &cmd);
	void checkIncantationResult(const std::string &cmd,
	                            unsigned int result);
	void checkTeamName(const std::string &cmd,
	                             const std::string &teamName);
	void checkBotId(const std::string &cmd, unsigned int id);
	void checkEggId(const std::string &cmd, unsigned int id);
	void checkOrientation(const std::string &cmd, unsigned int orientation);
	void checkLevel(const std::string &cmd, unsigned int level);
	void checkMessage(const std::string &cmd, const std::string &message);

	std::unique_ptr<Bot> &getBotById(unsigned int id);
	std::unique_ptr<Egg> &getEggById(unsigned int id);

	std::vector<std::unique_ptr<Bot>> &getBots();
	std::vector<std::unique_ptr<Egg>> &getEggs();
	Map &getMap();
	float getTimeUnit() const;
	void setTimeUnit(float timeUnit);

private:
	Map map;
	float timeUnit;
	std::vector<std::string> teamNames;
	std::vector<std::unique_ptr<Bot>> bots;
	std::vector<std::unique_ptr<Egg>> eggs;
};


#endif //PSU_ZAPPY_2017_DATA_HPP
