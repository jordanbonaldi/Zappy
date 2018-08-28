/*
** EPITECH PROJECT, 2018
** Player
** File description:
** Implementation of Player
*/

#include <iostream>
#include <algorithm>
#include <Utils.hpp>
#include <memory.h>
#include "Player.hpp"

#define FOOD_UNIT 126

Player::Player(const std::string &teamName, const std::string &machineName, bool debugVar, bool isGraphic)
	: teamName(teamName), level(1), actions(0), isAlive(true), machineName(machineName), state(FARMING), currentMessage(nullptr), isGraphic(isGraphic), isDebug(debugVar)
{
	frontTiles.resize(81);
	id = rand() % 1000000;
	debug("WELCOME");
}

void Player::connect(CommunicationHelper *communicationHelper)
{
	this->communicationHelper = communicationHelper;
}

void Player::play()
{
	while (isAlive)
	{
		refreshActions();
		switch (state) {
			case FARMING:
				processFarming();
				break;
			case WAITING:
				processWaiting();
				break;
			case LOOKING_FOR:
				processLookingFor();
				break;
		}
		if (state == FARMING && amIReadyForIncantation()) {
			debug(std::string("changing from " + stateToString(state) + " to " + stateToString(WAITING)));
			state = WAITING;
		}
	}
}

bool Player::getObject(Inventory::Resource object)
{
	std::string response;

	actions += communicationHelper->getObject(Inventory::getStringFromResource(object));
	response = getMessage();
	if (response == "ok")
		inventory.addToInventory(object);
	return response == "ok";
}

bool Player::dropObject(Inventory::Resource object)
{
	std::string response;

	actions += communicationHelper->dropObject(Inventory::getStringFromResource(object));
	response = getMessage();
	if (response == "ok")
		inventory.removeFromInventory(object);
	return response == "ok";
}

std::string Player::getMessage()
{
	std::string response = communicationHelper->receiveMessage();

	if (response == "dead") {
		isAlive = false;
		debug("DEAD " + stateToString(state));
		exit(0);
	}
	else if (response.compare(0, 7, "message") == 0) {
		//debug("MESSAGE = " + response);
		Message message = Message(response);
		if (isGraphic)
			graphicMessage = response;
		if (level == message.level &&
			id < message.id)
		{
			if (state != LOOKING_FOR)
			{
				debug(std::string("changing from " +
						  stateToString(state) +
						  " to " +
						  stateToString(LOOKING_FOR)));
				state = LOOKING_FOR;
			}
			if (currentMessage != nullptr)
				currentMessage.release();
			currentMessage = std::make_unique<Message>(response);
		}
		return getMessage();
	}
	else if (state != WAITING && response.compare(0, 18, "Elevation underway") == 0)
	{
		return getMessage();
	}
	else if (state != WAITING && response.compare(0, 13, "Current level") == 0)
	{
		++level;
		debug("LEVEL UP");
		debug(std::string("changing from " + stateToString(state) + " to " + stateToString(FARMING)));
		state = FARMING;
		if (!isGraphic)
			layEgg();
		return getMessage();
	}
	else if (response.compare(0, 5, "eject") == 0) {
		debug("EJECT = " + response);
		return getMessage();
	}
	return response;
}

void Player::move()
{
	actions += communicationHelper->move();
	getMessage();
}

void Player::turnRight()
{
	actions += communicationHelper->turnRight();
	getMessage();
}

void Player::turnLeft()
{
	actions += communicationHelper->turnLeft();
	getMessage();
}

bool Player::eject()
{
	actions += communicationHelper->eject();
	return getMessage() == "ok";
}

int Player::getNumberAvailible()
{
	std::string response;

	actions += communicationHelper->getTeamSlotsAvailible();
	response = getMessage();
	return atoi(response.c_str());
}

void Player::layEgg()
{
	if (getNumberAvailible() >= 1) {
		actions += communicationHelper->fork();
		getMessage();
		execChild();
	}
	else {
		debug("TOO MUCH PEOPLE");
	}
}

void Player::broadcast()
{
	actions += communicationHelper->broadcast(std::to_string(level) + " " + inventory.toString() + " " + std::to_string(id));
	getMessage();
}

void Player::prepareIncantation()
{
	pickAllContentFromTile(true);
	if (level == 1)
		dropObject(Inventory::LINEMATE);
	if (level == 2) {
		dropObject(Inventory::LINEMATE);
		dropObject(Inventory::DERAUMERE);
		dropObject(Inventory::SIBUR);
	}
	if (level == 3) {
		dropObject(Inventory::LINEMATE);
		dropObject(Inventory::LINEMATE);
		dropObject(Inventory::SIBUR);
		dropObject(Inventory::PHIRAS);
		dropObject(Inventory::PHIRAS);
	}
	if (level == 4) {
		dropObject(Inventory::LINEMATE);
		dropObject(Inventory::DERAUMERE);
		dropObject(Inventory::SIBUR);
		dropObject(Inventory::SIBUR);
		dropObject(Inventory::PHIRAS);
	}
	if (level == 5) {
		dropObject(Inventory::LINEMATE);
		dropObject(Inventory::DERAUMERE);
		dropObject(Inventory::DERAUMERE);
		dropObject(Inventory::SIBUR);
		dropObject(Inventory::MENDIANE);
		dropObject(Inventory::MENDIANE);
		dropObject(Inventory::MENDIANE);
	}
	if (level == 6) {
		dropObject(Inventory::LINEMATE);
		dropObject(Inventory::DERAUMERE);
		dropObject(Inventory::DERAUMERE);
		dropObject(Inventory::SIBUR);
		dropObject(Inventory::SIBUR);
		dropObject(Inventory::SIBUR);
		dropObject(Inventory::PHIRAS);
	}
	if (level == 7) {
		dropObject(Inventory::LINEMATE);
		dropObject(Inventory::LINEMATE);
		dropObject(Inventory::DERAUMERE);
		dropObject(Inventory::DERAUMERE);
		dropObject(Inventory::SIBUR);
		dropObject(Inventory::SIBUR);
		dropObject(Inventory::PHIRAS);
		dropObject(Inventory::PHIRAS);
		dropObject(Inventory::MENDIANE);
		dropObject(Inventory::MENDIANE);
		dropObject(Inventory::THYSTAME);
	}
}

void Player::startIncantation()
{
	std::string response;

	if (isGraphic)
		state = WAITING;
	debug("START INCANTATION");
	if (!isGraphic)
		prepareIncantation();
	actions += communicationHelper->startIncantation();
	response = getMessage();
	if (response != "ko")
	{
		response = getMessage();
		if (response.compare(0, 13, "Current level") == 0)
		{
			++level;
			debug("LEVEL UP");
			if (!isGraphic)
				layEgg();
		}
		else
		{
			debug("INCANTATION FAILED " + response);
			if (!isGraphic)
				eject();
		}
	}
	else {
		response = getMessage();
		debug("INCANTATION FAILED " + response);
	}
	debug(std::string("changing from " + stateToString(state) + " to " + stateToString(FARMING)));
	state = FARMING;
}

void Player::checkInventory()
{
	actions += communicationHelper->inventory();
	getMessage();
}

void Player::look()
{
	std::string response;

	actions += communicationHelper->look();
	response = getMessage();
	try {
		response = response.substr(1, response.size() - 2);
	}
	catch (const std::out_of_range &e) {
		return;
	}
	std::vector<std::string>tiles = Utils::split(response, ',');
	for (size_t i = 0; i < tiles.size(); ++i) {
		std::vector<std::string>entities = Utils::split(tiles[i], ' ');
		frontTiles[i].clear();
		for (const auto &entitie : entities)
		{
			if (!entitie.empty()) {
				frontTiles[i].push_back(
					Inventory::getResourceFromString(
						entitie));
			}
		}
	}
}

void Player::refreshActions()
{
	if (actions >= FOOD_UNIT)
	{
		actions -= FOOD_UNIT;
		inventory.removeFromInventory(Inventory::FOOD);
	}
}

bool Player::amIReadyForIncantation()
{
	if (level == 1 && inventory.linemate > 0)
		return true;
	if (level == 2 && inventory.linemate > 0 && inventory.deraumere > 0 && inventory.sibur > 0)
		return true;
	if (level == 3 && inventory.linemate > 1 && inventory.sibur > 0 && inventory.phiras > 1)
		return true;
	if (level == 4 && inventory.linemate > 0 && inventory.deraumere > 0 && inventory.sibur > 1 && inventory.phiras > 0)
		return true;
	if (level == 5 && inventory.linemate > 0 && inventory.deraumere > 1 && inventory.sibur > 0 && inventory.mendiane > 2)
		return true;
	if (level == 6 && inventory.linemate > 0 && inventory.deraumere > 1 && inventory.sibur > 2 && inventory.phiras > 0)
		return true;
	if (level == 7 && inventory.linemate > 1 && inventory.deraumere > 1 && inventory.sibur > 1 && inventory.mendiane > 1 && inventory.phiras > 1 && inventory.thystame > 0)
		return true;
	return false;
}

bool Player::pickAllFromType(Inventory::Resource res) {
	int n = static_cast<int>(std::count_if(frontTiles[0].begin(), frontTiles[0].end(), [&res](Inventory::Resource c){ return c == res;}));

	for (int i = 0; i < n; ++i) {
		getObject(res);
	}
	return true;
}

bool Player::pickAllContentFromTile(bool forcePick)
{
	if (std::count_if(frontTiles[0].begin(), frontTiles[0].end(), [](Inventory::Resource c){ return c == Inventory::PLAYER;}) == 1 || forcePick)
	{
		pickAllFromType(Inventory::FOOD);
		pickAllFromType(Inventory::PHIRAS);
		pickAllFromType(Inventory::MENDIANE);
		pickAllFromType(Inventory::LINEMATE);
		pickAllFromType(Inventory::SIBUR);
		pickAllFromType(Inventory::DERAUMERE);
		pickAllFromType(Inventory::THYSTAME);
	}
	return true;
}

void Player::execChild()
{
	int pid = fork();
	if (!pid) {
		if (execve(av0, argv, nullptr))
			exit(84);
	}
}

void Player::debug(const std::string &message)
{
	if (isDebug)
		std::cout << id << " [" << level << "]: " << message << std::endl;
}

void Player::processFarming()
{
	int random = rand() % 3;

	switch(random) {
		case 0:
			move();
			break;
		case 1:
			turnRight();
			move();
			break;
		case 2:
			turnLeft();
			move();
			break;
	}
	look();
	pickAllContentFromTile();
}

void Player::processWaiting()
{
	look();
	if ((countPlayersInCurrentTile() == 1 && level == 1)
	    || (countPlayersInCurrentTile() == 2 && level == 2)
	    || (countPlayersInCurrentTile() == 2 && level == 3)
	    || (countPlayersInCurrentTile() == 4 && level == 4)
	    || (countPlayersInCurrentTile() == 4 && level == 5)
	    || (countPlayersInCurrentTile() == 6 && level == 6)
	    || (countPlayersInCurrentTile() == 6 && level == 7)) {
		startIncantation();
	}
	else if ((countPlayersInCurrentTile() > 1 && level == 1)
		 || (countPlayersInCurrentTile() > 2 && level == 2)
		 || (countPlayersInCurrentTile() > 2 && level == 3)
		 || (countPlayersInCurrentTile() > 4 && level == 4)
		 || (countPlayersInCurrentTile() > 4 && level == 5)
		 || (countPlayersInCurrentTile() > 6 && level == 6)
		 || (countPlayersInCurrentTile() > 6 && level == 7)) {
		eject();
		debug("EJECT");
	}
	else
		broadcast();
}

void Player::processLookingFor()
{
	look();
	if ((countPlayersInCurrentTile() == 1 && level == 1)
	    || (countPlayersInCurrentTile() == 2 && level == 2)
	       || (countPlayersInCurrentTile() == 2 && level == 3)
		  || (countPlayersInCurrentTile() == 4 && level == 4)
		     || (countPlayersInCurrentTile() == 4 && level == 5)
			|| (countPlayersInCurrentTile() == 6 && level == 6)
			   || (countPlayersInCurrentTile() == 6 && level == 7)) {
		return;
	}
	switch (currentMessage->k) {
		case 0:
			break;
		case 1:
			move();
			break;
		case 2:
			move();
			turnLeft();
			move();
			break;
		case 3:
			turnLeft();
			move();
			break;
		case 4:
			turnLeft();
			move();
			turnLeft();
			move();
			break;
		case 5:
			turnLeft();
			turnLeft();
			move();
			break;
		case 6:
			turnRight();
			move();
			turnRight();
			move();
			break;
		case 7:
			turnRight();
			move();
			break;
		case 8:
			move();
			turnRight();
			move();
			break;
	}
	look();
	pickAllContentFromTile();
}

int Player::countPlayersInCurrentTile()
{
	return static_cast<int>(std::count_if(frontTiles[0].begin(), frontTiles[0].end(), [](Inventory::Resource c){ return c == Inventory::PLAYER;}));
}

std::string Player::stateToString(Player::State state)
{
	switch (state) {
		case FARMING:
			return "FARMING";
		case LOOKING_FOR:
			return "LOOKING_FOR";
		case WAITING:
			return "WAITING";
	}
	return "";
}

void Player::setArgv(char *av0, char ** argv)
{
	if (isGraphic)
	{
		av0 = strdup("./zappy_ai");
		argv[0] = strdup("./zappy_ai");
	}
	this->argv = argv;
	this->av0 = av0;
}

const std::vector<std::vector<Inventory::Resource>> &Player::getFrontTiles() const
{
	return frontTiles;
}

const Inventory &Player::getInventory() const
{
	return inventory;
}

const int &Player::getLevel() const
{
	return level;
}

Player::~Player()
{
	frontTiles.clear();
}