/*
** EPITECH PROJECT, 2018
** CommunicationHelper
** File description:
** Declaration of Tile
*/

#ifndef PSU_ZAPPY_2017_TILE_HPP
	#define PSU_ZAPPY_2017_TILE_HPP

#include <memory>
#include <vector>
#include <map>
#include <irrlicht/irrlicht.h>

#include "Resource.hpp"

class Tile {
public:
	Tile(char symbol = ' ');
	~Tile();

	void initResources();
	void initMeshes(irr::scene::ISceneManager *smgr, irr::u32 x, irr::u32 y,
			irr::u32 tilesize);
	irr::scene::IAnimatedMeshSceneNode *initResourcesMeshes(
		irr::scene::ISceneManager *smgr, Resource::Type type);
	char getSymbol() const;
	void setSymbol(char symbol);
	Resources &getResources();
	ResourcesNb getResourcesQuantity();
	void setResources(const std::vector<std::string> &args);

private:
	char symbol;
	Resources resources;
	irr::scene::ISceneNode *mesh;
	std::map<Resource::Type , irr::scene::ISceneNode *> resourcesMeshes;
public:
	irr::scene::ISceneNode *getMesh() const;
	std::map<Resource::Type, irr::scene::ISceneNode *> &getResourcesMeshes();
};


#endif //PSU_ZAPPY_2017_TILE_HPP
