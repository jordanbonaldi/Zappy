/*
** EPITECH PROJECT, 2018
** ResourceManager
** File description:
** Implementation of ResourceManager
*/

#include "ResourceManager.hpp"

std::map<ResourceManager::Name, std::string> ResourceManager::resourcesPaths = {
	{FLOOR, "res/floor.jpg"},
	{SELECTED_FLOOR, "res/selectedFloor.jpg"},
	{PLAYER_MODEL, "res/Character/character.md2"},
	{PLAYER_TEXTURE, "res/Character/character.png"},
	{EGG_MODEL, "res/Character/egg.obj"},
	{EGG_TEXTURE, "res/Character/egg.png"},
	{GEM_MODEL, "res/Gem/gem.obj"},
	{GEM_BLUE_TEXTURE, "res/Gem/blue.png"},
	{GEM_GREEN_TEXTURE, "res/Gem/green.png"},
	{GEM_RED_TEXTURE, "res/Gem/red.png"},
	{GEM_YELLOW_TEXTURE, "res/Gem/yellow.png"},
	{GEM_WHITE_TEXTURE, "res/Gem/white.png"},
	{GEM_PURPLE_TEXTURE, "res/Gem/purple.png"},
	{GEM_BLUE_ICON, "res/Icons/blue.png"},
	{GEM_GREEN_ICON, "res/Icons/green.png"},
	{GEM_RED_ICON, "res/Icons/red.png"},
	{GEM_YELLOW_ICON, "res/Icons/yellow.png"},
	{GEM_WHITE_ICON, "res/Icons/white.png"},
	{GEM_PURPLE_ICON, "res/Icons/purple.png"},
	{FOOD_ICON, "res/Icons/food.png"},
	{SKYDOME, "res/skybox.jpg"},
	{FONT, "res/myfont.xml"},
};

std::map<Resource::Type, ResourceManager::Name>
        ResourceManager::resourcesTextures = {
	{Resource::PHIRAS, GEM_BLUE_TEXTURE},
	{Resource::DERAUMERE, GEM_GREEN_TEXTURE},
	{Resource::SIBUR, GEM_RED_TEXTURE},
	{Resource::LINEMATE, GEM_YELLOW_TEXTURE},
	{Resource::MENDIANE, GEM_WHITE_TEXTURE},
	{Resource::THYSTAME, GEM_PURPLE_TEXTURE},
};

const std::string
ResourceManager::getResPath(ResourceManager::Name name)
{
	return resourcesPaths[name];
}

const std::string
ResourceManager::getResourceTexture(Resource::Type type)
{

	return getResPath(resourcesTextures[type]);
}