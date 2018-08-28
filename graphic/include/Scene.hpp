/*
** EPITECH PROJECT, 2018
** Scene
** File description:
** Declaration of Scene
*/

#ifndef PSU_ZAPPY_2017_SCENE_HPP
	#define PSU_ZAPPY_2017_SCENE_HPP

#include <vector>
#include <irrlicht/irrlicht.h>
#include "Map.hpp"
#include "EventManager.hpp"
#include "ResourceManager.hpp"
#include "Bot.hpp"
#include "HUD.hpp"
#include "Data.hpp"

class Scene
{
public:
	Scene();
	~Scene() = default;
	void init(Map &map);
	void drawMap(Map &map);
	void refresh(Data &data);
	void refreshDaylight(Map &map, int timeUnit);
	void refreshTiles(Map &map);
	void refreshPlayers(Data &data);
	void refreshPlayer(Data &data, Bot *player);
	void updatePlayerMovement(Map &map, Bot *player, irr::f32 timeUnit);
	void updatePlayerAngle(Bot *player);
	void initPlayer(Map &map, std::unique_ptr<Bot> &bot);
	void initEgg(Map &map, std::unique_ptr<Egg> &egg);
	void processEvents(Map &map);
	void selectTile(Map &map);
	void deselectTile(Map &map);
	void rotateCamera(Map &map);
	void cameraZoom(bool zoomIn);
	void justifyPos(Map &map, irr::core::vector3df &pos);
	const irr::video::SColor &getTeamColor(const std::string &team);
private:
	irr::scene::ICameraSceneNode *camera;
	irr::scene::ILightSceneNode *dayLight;
	irr::scene::ILightSceneNode *ambientLight;
	bool initialized;
	HUD hud;
	irr::core::vector2d<irr::s32> selectedPos;
	bool rotation;
	irr::s32 zoom;
	std::chrono::time_point<std::chrono::high_resolution_clock> start;
	std::vector<irr::video::SColor> colors;
	std::map<std::string, irr::video::SColor> teamColors;
};

bool operator==(const irr::core::vector3df &a, const pos_t &b);

#endif //PSU_ZAPPY_2017_SCENE_HPP
