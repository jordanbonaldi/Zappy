/*
** EPITECH PROJECT, 2018
** Resource
** File description:
** Declaration of Resource
*/

#ifndef PSU_ZAPPY_2017_RESOURCE_HPP
#define PSU_ZAPPY_2017_RESOURCE_HPP

#include <iostream>
#include <vector>
#include <map>
#include <memory>

class Resource {
public:
	enum Type {
		FOOD = 0,
		LINEMATE,
		DERAUMERE,
		SIBUR,
		MENDIANE,
		PHIRAS,
		THYSTAME
	};

	Resource(const Type &type, unsigned int quantity);

	Type getType() const;
	unsigned int getQuantity() const;

	void setQuantity(unsigned int quantity);
private:
	const Type type;
	unsigned int quantity;
};

typedef std::vector<std::unique_ptr<Resource>> Resources;
typedef std::map<Resource::Type, int> ResourcesNb;

#endif //PSU_ZAPPY_2017_RESOURCE_HPP
