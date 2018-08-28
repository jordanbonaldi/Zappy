/*
** EPITECH PROJECT, 2018
** Player
** File description:
** Declaration of Player
*/

#ifndef ZAPPY_AI_PLAYER_HPP
	#define ZAPPY_AI_PLAYER_HPP

#include <memory>
#include "Inventory.hpp"
#include "SocketClient.hpp"
#include "CommunicationHelper.hpp"
#include "Message.hpp"

class Player
{
public:
	enum State {
		FARMING,
		WAITING,
		LOOKING_FOR
	};
	Player(const std::string &teamName, const std::string &machineName, bool, bool = false);
	virtual ~Player();
	void connect(CommunicationHelper *communicationHelper);
	void setArgv(char *, char **);
	void play();
	const std::vector<std::vector<Inventory::Resource>> &getFrontTiles() const;
	const Inventory &getInventory() const;
	const int &getLevel() const;

public:
	std::string getMessage();
	bool getObject(Inventory::Resource object);
	bool dropObject(Inventory::Resource object);
	void move();
	void turnRight();
	void turnLeft();
	bool eject();
	int getNumberAvailible();
	void layEgg();
	void broadcast();
	void startIncantation();
	void checkInventory();
	void look();
	void refreshActions();
	bool amIReadyForIncantation();
	void execChild();
	bool pickAllContentFromTile(bool forcePick = false);
	bool pickAllFromType(Inventory::Resource res);
	void debug(const std::string &message);
	void processFarming();
	void processWaiting();
	void processLookingFor();
	std::string stateToString(State state);
	int countPlayersInCurrentTile();
	void prepareIncantation();
private:
	CommunicationHelper *communicationHelper;
	Inventory inventory;
	std::string teamName;
	int level;
	int actions;
	bool isAlive;
	std::string machineName;
	std::vector<std::vector<Inventory::Resource>> frontTiles;
	State state;
	std::unique_ptr<Message> currentMessage;
	long id;
	char *av0;
	char *const *argv;
	bool isGraphic;
	std::string graphicMessage;
	bool isDebug;
};

#endif //ZAPPY_AI_PLAYER_HPP
