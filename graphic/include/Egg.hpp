/*
** EPITECH PROJECT, 2018
** Egg
** File description:
** Definition of Egg
*/

#ifndef PSU_ZAPPY_2017_EGG_HPP
#define PSU_ZAPPY_2017_EGG_HPP

#include <irrlicht/IAnimatedMeshSceneNode.h>
#include "Map.hpp"

class Egg {
public:
	Egg(unsigned int id, pos_t pos, const std::string &team);
	~Egg();

	unsigned int getId() const;
	void setId(unsigned int id);
	const pos_t &getPos() const;
	void setPos(const pos_t &pos);
	const std::string &getTeam() const;
	bool isHatching() const;
	void setHatching(bool hatching);
	irr::scene::IAnimatedMeshSceneNode *getMesh() const;
	void setMesh(irr::scene::IAnimatedMeshSceneNode *mesh);
	bool isAlive() const;
	void setAlive(bool alive);

private:
	unsigned int id;
	pos_t pos;
	const std::string team;
	bool hatching;
	irr::scene::IAnimatedMeshSceneNode *mesh;
	bool alive;
};


#endif //PSU_ZAPPY_2017_EGG_HPP
