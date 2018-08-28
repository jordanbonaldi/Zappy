/*
** EPITECH PROJECT, 2018
** CommunicationHelper
** File description:
** Implementation of Bot
*/

#include "Bot.hpp"

Bot::Bot(unsigned int id, pos_t pos, Orientation orientation,
         unsigned int level, const std::string &team)
	: id(id), pos(pos), orientation(orientation), level(level), team(team),
	mesh(nullptr), levelLabel(nullptr), alive(true), status(Status::NORMAL), oldPos({-1, -1}),
	movement(false)
{
	initInventory();
}

Bot::~Bot()
{
	if (mesh)
		mesh->remove();
	if (levelLabel)
		levelLabel->remove();
}

void Bot::initInventory()
{
	inventory.push_back(std::make_unique<Resource>
		                    (Resource::Type::FOOD, 0));
	inventory.push_back(std::make_unique<Resource>
		                    (Resource::Type::LINEMATE, 0));
	inventory.push_back(std::make_unique<Resource>
		                    (Resource::Type::DERAUMERE, 0));
	inventory.push_back(std::make_unique<Resource>
		                    (Resource::Type::SIBUR, 0));
	inventory.push_back(std::make_unique<Resource>
		                    (Resource::Type::MENDIANE, 0));
	inventory.push_back(std::make_unique<Resource>
		                    (Resource::Type::PHIRAS, 0));
	inventory.push_back(std::make_unique<Resource>
		                    (Resource::Type::THYSTAME, 0));
}

const pos_t &Bot::getPos() const
{
	return pos;
}

void Bot::setPos(const pos_t &pos)
{
	lastMove = std::chrono::system_clock::now();
	if (oldPos.x != pos.x || oldPos.y != pos.y)
		setMovement(true);
	oldPos = Bot::pos;
	Bot::pos = pos;
}

unsigned int Bot::getLevel() const
{
	return level;
}

void Bot::setLevel(unsigned int level)
{
	Bot::level = level;
}

unsigned int Bot::getId() const
{
	return id;
}

void Bot::setId(unsigned int id)
{
	Bot::id = id;
}

const std::string &Bot::getTeam() const
{
	return team;
}

Orientation Bot::getOrientation() const
{
	return orientation;
}

void Bot::setOrientation(Orientation orientation)
{
	Bot::orientation = orientation;
}

Resources &Bot::getInventory()
{
	return inventory;
}

void Bot::setInventory(const std::vector<std::string> &args)
{
	unsigned long size = args.size();

	if (size != 11) {
		throw std::invalid_argument("setInventory: invalid number of"
			      " argument, expected 11, got " + size);
	}
	for (unsigned long i = 4; i < size; ++i) {
		inventory[i - 4]->setQuantity((unsigned int)stoi(args[i]));
	}
}

irr::scene::IAnimatedMeshSceneNode *Bot::getMesh() const
{
	return mesh;
}

void Bot::setMesh(irr::scene::IAnimatedMeshSceneNode *mesh)
{
	Bot::mesh = mesh;
}

void Bot::expulse()
{
	// TODO @Issam: add expulsion animation
	std::cout << "Bot " << id << " uses expulsion!" << std::endl;
}

void Bot::sendMessage(const std::string &message)
{
	setAnimation(irr::scene::EMAT_SALUTE);
	// TODO @Issam: display bot's message
	std::cout << ">> Bot " << id << " sends message '" <<
	          message << "'" << std::endl;
}

void Bot::die() {
	setAnimation(irr::scene::EMAT_DEATH_FALLFORWARD);
	alive = false;
}

bool Bot::isAlive() const
{
	return alive;
}

Bot::Status Bot::getStatus() const
{
	return status;
}

void Bot::setStatus(Bot::Status status)
{
	Bot::status = status;
}

void Bot::dropResource(Resource::Type resource) const
{
	(void)resource;
	// TODO @Issam: display "Player ... droped one ..."
}

void Bot::collectResource(Resource::Type resource) const
{
	(void)resource;
	// TODO @Issam: display "Player ... collected one ..."
}

const pos_t &Bot::getOldPos() const
{
	return oldPos;
}

const std::chrono::time_point<std::chrono::high_resolution_clock> &
Bot::getLastMove() const
{
	return lastMove;
}

void Bot::setAnimation(irr::scene::EMD2_ANIMATION_TYPE animation)
{
	if (Bot::animation == animation || !mesh)
		return;
	Bot::animation = animation;
	mesh->setMD2Animation(animation);
}

bool Bot::isMovement() const
{
	return movement;
}

void Bot::setMovement(bool movement)
{
	Bot::movement = movement;
}

irr::scene::ITextSceneNode *Bot::getLevelLabel() const
{
	return levelLabel;
}

void Bot::setLevelLabel(irr::scene::ITextSceneNode *levelLabel)
{
	Bot::levelLabel = levelLabel;
}
