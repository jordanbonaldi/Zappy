/*
** EPITECH PROJECT, 2018
** Egg
** File description:
** Implementation of Egg
*/

#include "Egg.hpp"

Egg::Egg(unsigned int id, pos_t pos, const std::string &team)
	: id(id), pos(pos), team(team), hatching(false), mesh(nullptr), alive(true)
{}

Egg::~Egg()
{
	if (mesh)
		mesh->remove();
}

unsigned int Egg::getId() const
{
	return id;
}

void Egg::setId(unsigned int id)
{
	Egg::id = id;
}

const pos_t &Egg::getPos() const
{
	return pos;
}

void Egg::setPos(const pos_t &pos)
{
	Egg::pos = pos;
}

const std::string &Egg::getTeam() const
{
	return team;
}

bool Egg::isHatching() const
{
	return hatching;
}

void Egg::setHatching(bool hatching)
{
	Egg::hatching = hatching;
}

bool Egg::isAlive() const
{
	return alive;
}

void Egg::setAlive(bool alive)
{
	Egg::alive = alive;
}

irr::scene::IAnimatedMeshSceneNode *Egg::getMesh() const
{
	return mesh;
}

void Egg::setMesh(irr::scene::IAnimatedMeshSceneNode *mesh)
{
	Egg::mesh = mesh;
}
