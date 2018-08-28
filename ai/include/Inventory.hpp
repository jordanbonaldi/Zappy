/*
** EPITECH PROJECT, 2018
** Inventory
** File description:
** Declaration of Inventory
*/

#ifndef ZAPPY_AI_INVENTORY_HPP
	#define ZAPPY_AI_INVENTORY_HPP

#include <string>

class Inventory
{
public:
	enum Resource {
		FOOD,
		LINEMATE,
		DERAUMERE,
		SIBUR,
		MENDIANE,
		PHIRAS,
		THYSTAME,
		PLAYER,
	};
	Inventory();
	static std::string getStringFromResource(Resource res);
	static Resource getResourceFromString(const std::string &res);
	void addToInventory(Resource res);
	void removeFromInventory(Resource res);
	std::string toString();
	int food;
	int linemate;
	int deraumere;
	int sibur;
	int mendiane;
	int phiras;
	int thystame;
};

#endif //ZAPPY_AI_INVENTORY_HPP
