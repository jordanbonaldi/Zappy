/*
** EPITECH PROJECT, 2018
** CommunicationHelper
** File description:
** Declaration of Bot
*/

#ifndef PSU_ZAPPY_2017_BOT_HPP
#define PSU_ZAPPY_2017_BOT_HPP

#include <iostream>
#include <irrlicht/irrlicht.h>
#include <chrono>

#include "Map.hpp"

enum Orientation {
	NORTH = 1,
	EAST,
	SOUTH,
	WEST
};

class Bot {
public:
	enum Status {
		NORMAL,
		INCANTING,
		LAYING
	};

	Bot(unsigned int id, pos_t pos, Orientation orientation,
	    unsigned int level, const std::string &team);
	~Bot();

	void dropResource(Resource::Type resource) const;
	void collectResource(Resource::Type resource) const;
	bool isAlive() const;
	void die();
	void expulse();
	void sendMessage(const std::string &message);
	Resources &getInventory();
	void setInventory(const std::vector<std::string> &args);
	void initInventory();
	const pos_t &getPos() const;
	void setPos(const pos_t &pos);
	unsigned int getLevel() const;
	void setLevel(unsigned int level);
	unsigned int getId() const;
	void setId(unsigned int id);
	const std::string &getTeam() const;
	Orientation getOrientation() const;
	void setOrientation(Orientation orientation);
	irr::scene::IAnimatedMeshSceneNode *getMesh() const;
	void setMesh(irr::scene::IAnimatedMeshSceneNode *mesh);
	Status getStatus() const;
	void setStatus(Status status);
	const pos_t &getOldPos() const;
	const std::chrono::time_point<std::chrono::high_resolution_clock>
		&getLastMove() const;
	void setAnimation(irr::scene::EMD2_ANIMATION_TYPE animation);
	irr::scene::ITextSceneNode *getLevelLabel() const;
	void setLevelLabel(irr::scene::ITextSceneNode *levelLabel);
private:
	unsigned int id;
	pos_t pos;
	Orientation orientation;
	unsigned int level;
	const std::string team;
	Resources inventory;
	irr::scene::IAnimatedMeshSceneNode *mesh;
	irr::scene::ITextSceneNode *levelLabel;
	bool alive;
	Status status;
	pos_t oldPos;
	std::chrono::time_point<std::chrono::high_resolution_clock> lastMove;
	irr::scene::EMD2_ANIMATION_TYPE animation;
	bool movement;
public:
	bool isMovement() const;
	void setMovement(bool movement);
};


#endif //PSU_ZAPPY_2017_BOT_HPP
