/*
** EPITECH PROJECT, 2018
** Message
** File description:
** Declaration of Message
*/

#ifndef ZAPPY_AI_MESSAGE_HPP
	#define ZAPPY_AI_MESSAGE_HPP

#include "Inventory.hpp"

class Message : public Inventory
{
public:
	explicit Message(const std::string &string);
	int level;
	int k;
	int id;
};

#endif //ZAPPY_AI_MESSAGE_HPP
