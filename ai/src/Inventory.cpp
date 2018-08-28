/*
** EPITECH PROJECT, 2018
** Inventory
** File description:
** Implementation of Inventory
*/

#include <stdexcept>
#include "Inventory.hpp"

Inventory::Inventory() : food(9), linemate(0), deraumere(0), sibur(0), mendiane(0), phiras(0), thystame(0)
{

}

std::string Inventory::getStringFromResource(Inventory::Resource res)
{
	switch (res)
	{
		case FOOD:
			return "food";
		case LINEMATE:
			return "linemate";
		case DERAUMERE:
			return "deraumere";
		case SIBUR:
			return "sibur";
		case MENDIANE:
			return "mendiane";
		case PHIRAS:
			return "phiras";
		case THYSTAME:
			return "thystame";
		case PLAYER:
			return "player";
		default:
			return "";
	}
}

void Inventory::addToInventory(Inventory::Resource res)
{
	switch (res)
	{
		case FOOD:
			++food;
			break;
		case LINEMATE:
			++linemate;
			break;
		case DERAUMERE:
			++deraumere;
			break;
		case SIBUR:
			++sibur;
			break;
		case MENDIANE:
			++mendiane;
			break;
		case PHIRAS:
			++phiras;
			break;
		case THYSTAME:
			++thystame;
			break;
		default:
			break;
	}
}

void Inventory::removeFromInventory(Inventory::Resource res)
{
	switch (res)
	{
		case FOOD:
			--food;
			break;
		case LINEMATE:
			--linemate;
			break;
		case DERAUMERE:
			--deraumere;
			break;
		case SIBUR:
			--sibur;
			break;
		case MENDIANE:
			--mendiane;
			break;
		case PHIRAS:
			--phiras;
			break;
		case THYSTAME:
			--thystame;
			break;
		default:
			break;
	}
}

Inventory::Resource Inventory::getResourceFromString(const std::string &res)
{
	if (res == "food")
		return FOOD;
	if (res == "linemate")
		return LINEMATE;
	if (res == "deraumere")
		return DERAUMERE;
	if (res == "sibur")
		return SIBUR;
	if (res == "mendiane")
		return MENDIANE;
	if (res == "phiras")
		return PHIRAS;
	if (res == "thystame")
		return THYSTAME;
	if (res == "player")
		return PLAYER;
	throw std::invalid_argument(res);
}

std::string Inventory::toString()
{
	return std::to_string(food) + " " +
		std::to_string(linemate) + " " +
		std::to_string(deraumere) + " " +
		std::to_string(sibur) + " " +
		std::to_string(mendiane) + " " +
		std::to_string(phiras) + " " +
		std::to_string(thystame);
}
