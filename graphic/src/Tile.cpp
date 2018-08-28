/*
** EPITECH PROJECT, 2018
** CommunicationHelper
** File description:
** Implementation of Tile
*/

#include <ResourceManager.hpp>
#include "Tile.hpp"

Tile::Tile(char symbol) : symbol(symbol), mesh(nullptr),
	resourcesMeshes()
{
	initResources();
}

Tile::~Tile()
{
	for (auto item : resourcesMeshes) {
		if (item.second)
			item.second->remove();
	}
}

void Tile::initResources()
{
	resources.push_back(std::make_unique<Resource>
	        (Resource::Type::FOOD, 0));
	resources.push_back(std::make_unique<Resource>
	        (Resource::Type::LINEMATE, 0));
	resources.push_back(std::make_unique<Resource>
	        (Resource::Type::DERAUMERE, 0));
	resources.push_back(std::make_unique<Resource>
	        (Resource::Type::SIBUR, 0));
	resources.push_back(std::make_unique<Resource>
	        (Resource::Type::MENDIANE, 0));
	resources.push_back(std::make_unique<Resource>
	        (Resource::Type::PHIRAS, 0));
	resources.push_back(std::make_unique<Resource>
	        (Resource::Type::THYSTAME, 0));
}

void Tile::initMeshes(irr::scene::ISceneManager *smgr, irr::u32 x, irr::u32 y,
		irr::u32 tilesize)
{
	const irr::scene::IGeometryCreator *g= smgr->getGeometryCreator();
	irr::scene::IMesh *plane = g->createPlaneMesh(
		irr::core::dimension2d<irr::f32>((irr::f32)tilesize,
						(irr::f32)tilesize));
	mesh = smgr->addMeshSceneNode(plane);
	mesh->setPosition(irr::core::vector3df((irr::f32)x * tilesize,
						0,
						(irr::f32)y * tilesize * -1));
	mesh->setMaterialType(irr::video::EMT_SOLID);
	mesh->setMaterialFlag(irr::video::EMF_NORMALIZE_NORMALS, true);
	mesh->setMaterialTexture(0,
		smgr->getVideoDriver()->getTexture("res/floor.jpg"));
	resourcesMeshes[Resource::Type::LINEMATE] = initResourcesMeshes(smgr,
		Resource::Type::LINEMATE);
	resourcesMeshes[Resource::Type::DERAUMERE] = initResourcesMeshes(smgr,
		Resource::Type::DERAUMERE);
	resourcesMeshes[Resource::Type::SIBUR] = initResourcesMeshes(smgr,
		Resource::Type::SIBUR);
	resourcesMeshes[Resource::Type::MENDIANE] = initResourcesMeshes(smgr,
		Resource::Type::MENDIANE);
	resourcesMeshes[Resource::Type::PHIRAS] = initResourcesMeshes(smgr,
		Resource::Type::PHIRAS);
	resourcesMeshes[Resource::Type::THYSTAME] = initResourcesMeshes(smgr,
		Resource::Type::THYSTAME);
}

irr::scene::IAnimatedMeshSceneNode *Tile::initResourcesMeshes(
	irr::scene::ISceneManager *smgr, Resource::Type type)
{
	auto mesh = smgr->getMesh(
		ResourceManager::getResPath(
			ResourceManager::GEM_MODEL).c_str());

	auto animatedMeshSceneNode = smgr->addAnimatedMeshSceneNode(mesh);
	animatedMeshSceneNode->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	animatedMeshSceneNode->setMaterialTexture(0,
		smgr->getVideoDriver()->getTexture(
			ResourceManager::getResourceTexture(type).c_str()));
	animatedMeshSceneNode->setScale(irr::core::vector3df(3, 3, 3));
	return animatedMeshSceneNode;
}

char Tile::getSymbol() const {
	return symbol;
}

void Tile::setSymbol(char symbol) {
	Tile::symbol = symbol;
}

Resources &Tile::getResources()
{
	return resources;
}

void Tile::setResources(const std::vector<std::string> &args)
{
	unsigned long size = args.size();

	if (size != 10) {
		throw std::invalid_argument("setRessources: Invalid number of "
		                            "argument, expected 10, got" + size);
	}
	for (unsigned long i = 3; i < size; ++i) {
		resources[i - 3]->setQuantity((unsigned int)stoi(args[i]));
	}
}

ResourcesNb Tile::getResourcesQuantity()
{
	ResourcesNb ret = {
		{Resource::FOOD, 0},
		{Resource::LINEMATE, 0},
		{Resource::DERAUMERE, 0},
		{Resource::SIBUR, 0},
		{Resource::MENDIANE, 0},
		{Resource::PHIRAS, 0},
		{Resource::THYSTAME, 0}
	};

	for (std::unique_ptr<Resource> &res : resources) {
		ret[res.get()->getType()] = res.get()->getQuantity();
	}
	return ret;
}

irr::scene::ISceneNode *Tile::getMesh() const
{
	return mesh;
}

std::map<Resource::Type, irr::scene::ISceneNode *> &Tile::getResourcesMeshes()
{
	return resourcesMeshes;
}
