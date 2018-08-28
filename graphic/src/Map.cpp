/*
** EPITECH PROJECT, 2018
** Core
** File description:
** Implementation of Map
*/

#include "Map.hpp"

Map::Map() : size({0, 0}), tiles(), tilesize(20)
{}

const pos_t &Map::getSize() const
{
	return size;
}

std::vector<std::vector<std::unique_ptr<Tile>>> &Map::getTiles()
{
	return tiles;
}

bool Map::isInitialized() const
{
	return !tiles.empty();
}

void Map::initialize(pos_t size)
{
	for (auto y = 0 ; y < size.y ; y++) {
		tiles.emplace_back();
		for (auto x = 0 ; x < size.x ; x++) {
			tiles[y].push_back(std::make_unique<Tile> (' '));
		}
	}
	this->size = size;
}

void Map::print() {
	for (const auto &tileLine: tiles) {
		for (const auto &tile: tileLine) {
			std::cout << tile->getSymbol();
		}
		std::cout << std::endl;
	}
}

std::vector<std::unique_ptr<Tile>> &Map::operator[](unsigned int i)
{
	return tiles.at(i);
}

void Map::printResources()
{
	for (unsigned int y = 0 ; y < tiles.size() ; y++) {
		for (unsigned int x = 0 ; x < tiles[y].size() ; x++) {
			auto &tileResources = tiles[y][x]->getResources();
			std::cout << "Tile (" << x << "," << y
			          << "): FOOD(" << tileResources[0]->getQuantity()
			          << ") LINEMATE(" << tileResources[1]->getQuantity()
			          << ") DERAUMERE(" << tileResources[2]->getQuantity()
			          << ") SIBUR(" << tileResources[3]->getQuantity()
			          << ") MENDIANE(" << tileResources[4]->getQuantity()
			          << ") PHIRAS(" << tileResources[5]->getQuantity()
			          << ") THYSTAME(" << tileResources[6]->getQuantity()
			          << ")" << std::endl;
		}
	}
}

irr::u32 Map::getWidth() const
{
	return size.x * tilesize;
}

irr::u32 Map::getHeight() const
{
	return size.y * tilesize;
}

irr::u32 Map::getTilesize() const
{
	return tilesize;
}
