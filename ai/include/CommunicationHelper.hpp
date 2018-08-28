/*
** EPITECH PROJECT, 2018
** CommunicationHelper
** File description:
** Declaration of CommunicationHelper
*/

#ifndef ZAPPY_AI_COMMUNICATIONHELPER_HPP
	#define ZAPPY_AI_COMMUNICATIONHELPER_HPP

#include <vector>
#include "SocketClient.hpp"

class CommunicationHelper
{
public:
	explicit CommunicationHelper(int);
	bool connection(const std::string &);
	const std::string receiveMessage() const;
	void sendMessage(const std::string &message) const;
	int look() const;
	int turnRight() const;
	int turnLeft() const;
	int move() const;
	int inventory() const;
	int broadcast(const std::string &message) const;
	int getTeamSlotsAvailible() const;
	int fork() const;
	int eject() const;
	int getObject(const std::string &object) const;
	int dropObject(const std::string &object) const;
	int startIncantation() const;
	void disconnection();
private:
	SocketClient socketClient;
	int clientNum;
	std::pair<int, int>mapSize;
};

#endif //ZAPPY_AI_COMMUNICATIONHELPER_HPP
