/*
** EPITECH PROJECT, 2018
** ResourceManager
** File description:
** Declaration of ResourceManager
*/

#ifndef PSU_ZAPPY_2017_RESOURCEMANAGER_HPP
	#define PSU_ZAPPY_2017_RESOURCEMANAGER_HPP

#include <string>
#include <map>
#include "Resource.hpp"

class ResourceManager
{
public:
	enum Name {
		FLOOR,
		SELECTED_FLOOR,
		PLAYER_MODEL,
		PLAYER_TEXTURE,
		EGG_MODEL,
		EGG_TEXTURE,
		GEM_MODEL,
		GEM_BLUE_TEXTURE,
		GEM_GREEN_TEXTURE,
		GEM_RED_TEXTURE,
		GEM_YELLOW_TEXTURE,
		GEM_WHITE_TEXTURE,
		GEM_PURPLE_TEXTURE,
		GEM_BLUE_ICON,
		GEM_GREEN_ICON,
		GEM_RED_ICON,
		GEM_YELLOW_ICON,
		GEM_WHITE_ICON,
		GEM_PURPLE_ICON,
		FOOD_ICON,
		SKYDOME,
		FONT
	};
	static const std::string getResPath(Name name);
	static const std::string getResourceTexture(Resource::Type type);
private:
	static std::map<Name, std::string> resourcesPaths;
	static std::map<Resource::Type, ResourceManager::Name> resourcesTextures;
};


#endif //PSU_ZAPPY_2017_RESOURCEMANAGER_HPP
