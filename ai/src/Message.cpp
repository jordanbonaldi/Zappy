/*
** EPITECH PROJECT, 2018
** Message
** File description:
** Implementation of Message
*/

#include <vector>
#include <iostream>
#include "Message.hpp"
#include "Utils.hpp"

Message::Message(const std::string &string)
{
	int i = 0;

	std::vector<std::string> message = Utils::split(string, ',');

	k = message[0][message[0].size() - 1] - '0';

//	std::cout << ">>>>>>>>>>>>>>>>><" << k << std::endl;
	std::vector<std::string> content = Utils::split(message[1], ' ');

	if (content[i] == "")
		++i;
	level = atoi(content[i++].c_str());
	food = atoi(content[i++].c_str());
	linemate = atoi(content[i++].c_str());
	deraumere = atoi(content[i++].c_str());
	sibur = atoi(content[i++].c_str());
	mendiane = atoi(content[i++].c_str());
	phiras = atoi(content[i++].c_str());
	thystame = atoi(content[i++].c_str());
	id = atoi(content[i++].c_str());
}
