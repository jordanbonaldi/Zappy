/*
** EPITECH PROJECT, 2018
** Core
** File description:
** Implementation of Data
*/

#include "Data.hpp"

Data::Data()
{}

Map &Data::getMap()
{
	return map;
}

float Data::getTimeUnit() const {
	return timeUnit;
}

void Data::setTimeUnit(float timeUnit) {
	Data::timeUnit = timeUnit;
}

void Data::addTeamName(const std::string &name)
{
	teamNames.push_back(name);
}

bool Data::doesTeamNameExists(const std::string &name) const
{
	return std::find(teamNames.begin(), teamNames.end(), name) != teamNames.end();
}

void Data::printTeamNames()
{
	std::cout << "Team names:" << std::endl;
	for (const auto &name: teamNames)
		std::cout << "\t" << name << std::endl;
}

void Data::printBots()
{
	std::cout << "Bots:" << std::endl;
	for (const auto &bot: bots) {
		std::cout << "Bot: " << bot->getId() <<
		          " | " << bot->getPos().x <<
		          " | " << bot->getPos().y <<
		          " | " << bot->getOrientation() <<
		          " | " << bot->getLevel() <<
		          " | " << bot->getTeam() << std::endl;
	}
}

std::vector<std::unique_ptr<Bot>> &Data::getBots()
{
	return bots;
}

std::vector<std::unique_ptr<Egg>> &Data::getEggs()
{
	return eggs;
}

void Data::checkPos(const std::string &cmd, const pos_t &pos)
{
	if (pos.x >= map.getSize().x || pos.x < 0) {
		throw std::invalid_argument(cmd + ": X position is out of range");
	} else if (pos.y >= map.getSize().y || pos.y < 0) {
		throw std::invalid_argument(cmd + ": Y position is out of range");
	}
}

void Data::checkArgNumber(const std::string &cmd, unsigned int argsSize,
                          unsigned int expectedSize)
{
	if (argsSize != expectedSize) {
		throw std::invalid_argument(
			cmd + ": invalid number of argument, expected " +
			std::to_string(expectedSize) + ", got " +
			std::to_string(argsSize));
	}
}

void Data::checkInitializedMap(const std::string &cmd)
{
	if (map.isInitialized()) {
		throw std::invalid_argument(
			cmd + ": Map is already initialized");
	}
}

void Data::checkTeamName(const std::string &cmd,
                                   const std::string &teamName)
{
	if (!doesTeamNameExists(teamName)) {
		throw std::invalid_argument(
			cmd + ": Team name '" + teamName +
			"' isn't registered");
	}
}

void Data::checkBotId(const std::string &cmd, unsigned int id)
{
	auto it = std::find_if(bots.begin(), bots.end(),
		[&](std::unique_ptr<Bot> &bot) {
		return bot->getId() == id;
	});
	if (it == bots.end()) {
		throw std::invalid_argument(
			cmd + ": bot '"+ std::to_string(id) +
			"' doesn't exist");
	}
}

void Data::checkEggId(const std::string &cmd, unsigned int id)
{
	auto it = std::find_if(eggs.begin(), eggs.end(),
		[&](std::unique_ptr<Egg> &egg) {
		return egg->getId() == id;
	});
	if (it == eggs.end()) {
		throw std::invalid_argument(
			cmd + ": egg '"+ std::to_string(id) +
			"' doesn't exist");
	}
}

std::unique_ptr<Bot> &Data::getBotById(unsigned int id)
{
	auto it = std::find_if(bots.begin(), bots.end(),
               [&](std::unique_ptr<Bot> &bot) {
                       return bot->getId() == id;
               });
	return *it;
}

std::unique_ptr<Egg> &Data::getEggById(unsigned int id)
{
	auto it = std::find_if(eggs.begin(), eggs.end(),
               [&](std::unique_ptr<Egg> &egg) {
                       return egg->getId() == id;
               });
	return *it;
}

void Data::checkOrientation(const std::string &cmd, unsigned int orientation)
{
	if (!orientation || orientation > 4) {
		throw std::invalid_argument(
			cmd + ": invalid orientation value " +
			std::to_string(orientation));
	}
}

void Data::checkLevel(const std::string &cmd, unsigned int level)
{
	if (level < 1 || level > 8) {
		throw std::invalid_argument(
			cmd + ": invalid level value " +
			std::to_string(level));
	}
}

void Data::checkMessage(const std::string &cmd, const std::string &message)
{
	if (message.empty()) {
		throw std::invalid_argument(cmd + ": message is empty");
	}
}

void Data::destroyDeadBots()
{
	unsigned long size = bots.size();

	for (unsigned long i = 0; i < size; ++i) {
		if (!bots[i]->isAlive()) {
			bots.erase(bots.begin() + i);
			destroyDeadBots();
			break;
		}
	}
}

void Data::destroyDeadEggs()
{
	unsigned long size = eggs.size();

	for (unsigned long i = 0; i < size; ++i) {
		if (!eggs[i]->isAlive()) {
			eggs.erase(eggs.begin() + i);
			destroyDeadEggs();
			break;
		}
	}
}

void Data::removeTeamName(const std::string &name)
{
	auto it = std::find(teamNames.begin(), teamNames.end(), name);
	teamNames.erase(it);
}

void Data::checkArgAtLeastNumber(const std::string &cmd, unsigned int argsSize,
                                 unsigned int expectedSize)
{
	if (argsSize < expectedSize) {
		throw std::invalid_argument(
			cmd +
			": invalid number of argument, expected at least" +
			std::to_string(expectedSize) + ", got " +
			std::to_string(argsSize));
	}
}

std::string Data::extractMessage(const std::vector<std::string> &args,
                                 unsigned int n)
{
	std::string msg;

	for (; n < args.size() ; n++) {
		n != args.size() - 1 ? msg += args[n] + " " : msg += args[n];
	}
	return msg;
}

void Data::checkIncantationResult(const std::string &cmd, unsigned int result)
{
	if (result > 8) {
		throw std::invalid_argument(
			cmd + ": invalid incantation result '" +
			std::to_string(result) + "'");
	}
}

void Data::checkResourceId(const std::string &cmd, unsigned int id)
{
	if (id > 6) {
		throw std::invalid_argument(
			cmd + ": invalid resource id " + std::to_string(id));
	}
}

void Data::printEggs()
{
	std::cout << "Eggs: ";
	for (const auto &egg: eggs) {
		std::cout << egg->getId() << " ";
	}
	std::cout << std::endl;
}
