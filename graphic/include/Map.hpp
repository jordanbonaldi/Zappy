/*
** EPITECH PROJECT, 2018
** Core
** File description:
** Declaration of Map
*/

#ifndef PSU_ZAPPY_2017_MAP_HPP
	#define PSU_ZAPPY_2017_MAP_HPP

#include <iostream>
#include <vector>
#include <memory>
#include <irrlicht/irrTypes.h>

#include "Tile.hpp"

typedef struct pos_s {
	int x;
	int y;
} pos_t;

class Map {
public:
	Map();

	std::vector<std::unique_ptr<Tile>> &operator[](unsigned int i);
	void initialize(pos_t size);
	bool isInitialized() const;
	void print();
	void printResources();
	const pos_t &getSize() const;
	std::vector<std::vector<std::unique_ptr<Tile>>> &getTiles();
	irr::u32 getWidth() const;
	irr::u32 getHeight() const;
	irr::u32 getTilesize() const;

private:
	pos_t size;
	std::vector<std::vector<std::unique_ptr<Tile>>> tiles;
	irr::u32 tilesize;
};


#endif //PSU_ZAPPY_2017_MAP_HPP
