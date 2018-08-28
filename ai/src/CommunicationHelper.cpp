/*
** EPITECH PROJECT, 2018
** CommunicationHelper
** File description:
** Implementation of CommunicationHelper
*/

#include <iostream>
#include "CommunicationHelper.hpp"

CommunicationHelper::CommunicationHelper(int port) : socketClient("127.0.0.1", port)
{

}

bool CommunicationHelper::connection(const std::string &teamName)
{
	std::string response;
	std::string map;

	socketClient.create();
	socketClient.connection();
	receiveMessage();
	sendMessage(teamName);
	if ((response = receiveMessage()) == "ko")
	{
		std::cerr << "Team name doesn't exist or there is not enough slot in team" << std::endl;
		return false;
	}
	clientNum = atoi(response.c_str());
	map = receiveMessage();
	return true;
}

const std::string CommunicationHelper::receiveMessage() const
{
	return socketClient.receiveMessage();
}

void CommunicationHelper::sendMessage(const std::string &message) const
{
	socketClient.sendMessage(message + "\n");
}

int CommunicationHelper::look() const
{
	sendMessage("Look\n");
	return 7;
}

int CommunicationHelper::turnRight() const
{
	sendMessage("Right\n");
	return 7;
}

int CommunicationHelper::turnLeft() const
{
	sendMessage("Left\n");
	return 7;
}

int CommunicationHelper::move() const
{
	sendMessage("Forward\n");
	return 7;
}

int CommunicationHelper::inventory() const
{
	sendMessage("Inventory\n");
	return 1;
}

int CommunicationHelper::broadcast(const std::string &message) const
{
	sendMessage("Broadcast " + message + "\n");
	return 7;
}

int CommunicationHelper::getTeamSlotsAvailible() const
{
	sendMessage("Connect_nbr\n");
	return 0;
}

int CommunicationHelper::fork() const
{
	sendMessage("Fork\n");
	return 42;
}

int CommunicationHelper::eject() const
{
	sendMessage("Eject\n");
	return 7;
}

int CommunicationHelper::getObject(const std::string &object) const
{
	sendMessage("Take " + object + "\n");
	return 7;
}

int CommunicationHelper::dropObject(const std::string &object) const
{
	sendMessage("Set " + object + "\n");
	return 7;
}

int CommunicationHelper::startIncantation() const
{
	sendMessage("Incantation\n");
	return 300;
}

void CommunicationHelper::disconnection()
{
	socketClient.disconnection();
}
