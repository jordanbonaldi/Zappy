/*
** EPITECH PROJECT, 2018
** Scene
** File description:
** Implementation of Scene
*/

#include "Window.hpp"
#include "Scene.hpp"

Scene::Scene() : initialized(false), selectedPos(-1, -1), rotation(false),
	zoom(100)
{
	colors = {
		{irr::video::SColor(255, 255, 0, 0)},
		{irr::video::SColor(255, 0, 0, 255)},
		{irr::video::SColor(255, 0, 255, 0)},
		{irr::video::SColor(255, 255, 255, 0)},
		{irr::video::SColor(255, 255, 0, 255)}
	};
	start = std::chrono::system_clock::now();
	hud.setUnselected();
}

void Scene::init(Map &map)
{
	irr::scene::ISceneManager *smgr = Window::device->getSceneManager();

	camera = Window::device->getSceneManager()->addCameraSceneNode();
	camera->setPosition(irr::core::vector3df(map.getWidth() / 2, 200,
		(irr::f32)(map.getHeight() * -1.1)));
	camera->setTarget(irr::core::vector3df(map.getWidth() / 2,
		0,
		(irr::f32)(map.getHeight() * -0.5)));
	camera->setFarValue(100000.0f);
	dayLight = Window::device->getSceneManager()->addLightSceneNode(0,
		irr::core::vector3df(map.getWidth() / 2, map.getWidth(),
				(irr::f32)map.getHeight() / 2 * -1),
		irr::video::SColor(255, 255, 255, 220), map.getWidth());
	ambientLight = Window::device->getSceneManager()->addLightSceneNode(0,
		irr::core::vector3df(map.getWidth() / 2, 300,
		(irr::f32)map.getHeight() / 2 * -1),
			irr::video::SColor(150, 100, 100, 255), 300.0f);
	ambientLight->enableCastShadow(false);
	drawMap(map);
	smgr->addSkyDomeSceneNode(smgr->getVideoDriver()->getTexture(
		ResourceManager::getResPath(ResourceManager::SKYDOME).c_str()),
			16, 8, 0.95f, 2.0f);
	initialized = true;
}

void Scene::drawMap(Map &map)
{
	irr::scene::ISceneManager *smgr = Window::device->getSceneManager();

	for (unsigned int y = 0; y < map.getTiles().size(); y++) {
		for (unsigned int x = 0; x < map.getTiles()[0].size(); x++) {
			map.getTiles()[y][x].get()->initMeshes(smgr, x, y,
				map.getTilesize());
		}
	}
}

void Scene::refresh(Data &data)
{
	auto &map = data.getMap();

	if (!initialized && map.getSize().x > 0 && map.getSize().y > 0)
		init(map);
	else if (initialized) {
		processEvents(map);
		refreshPlayers(data);
		if (selectedPos.X != -1 && selectedPos.Y != -1)
			hud.setSelected(*map[selectedPos.Y][selectedPos.X].get());
		refreshTiles(map);
		refreshDaylight(map, data.getTimeUnit());
		hud.refresh(data);
	}
	Window::device->getSceneManager()->drawAll();
	Window::device->getGUIEnvironment()->drawAll();
}

void Scene::refreshTiles(Map &map)
{
	for (unsigned int y = 0; y < map.getTiles().size(); y++) {
		for (unsigned int x = 0; x < map.getTiles()[0].size(); x++) {
			int resourceNb = 0;
			Tile *currentTile = map[y][x].get();
			auto &resourcesMeshes = currentTile->getResourcesMeshes();
			for (auto &resource : currentTile->getResources()) {
				auto type = resource.get()->getType();
				if (type == Resource::Type::FOOD)
					continue;
				if (resource.get()->getQuantity() == 0) {
					resourcesMeshes[type]->setVisible(false);
					continue;
				}
				auto pos = irr::core::vector3df(
					(irr::f32)(x * map.getTilesize()
						- map.getTilesize() * 0.3 + resourceNb % 3 * 5),
					3,
					(irr::f32)(y * (irr::f32)map.getTilesize()
						* -1 + map.getTilesize() * 0.3 - resourceNb / 3 * 5));
				resourcesMeshes[type]->setPosition(pos);
				resourcesMeshes[type]->setVisible(true);
				resourceNb++;
			}
		}
	}
}

void Scene::refreshPlayers(Data &data)
{
	auto &map = data.getMap();
	auto &players = data.getBots();
	auto &eggs = data.getEggs();

	for (std::unique_ptr<Bot> &bot : players) {
		if (!bot.get()->getMesh()) {
			initPlayer(map, bot);
		}
		else
			refreshPlayer(data, bot.get());
	}
	for (std::unique_ptr<Egg> &egg : eggs) {
		if (!egg.get()->getMesh())
			initEgg(map, egg);
	}
}

void Scene::refreshPlayer(Data &data, Bot *player)
{
	auto &map = data.getMap();
	auto level = player->getLevelLabel();
	auto pos = player->getMesh()->getPosition();

	updatePlayerMovement(map, player, data.getTimeUnit());
	updatePlayerAngle(player);
	if (player->getStatus() == Bot::Status::LAYING)
		player->setAnimation(irr::scene::EMAT_CROUCH_STAND);
	if (level) {
		pos.Y += 30;
		level->setText(irr::core::stringw(player->getLevel()).c_str());
		level->setPosition(pos);
		//set team color
		//level->setTextColor();
	}
}

void Scene::updatePlayerAngle(Bot *player)
{
	auto angle = 0;
	switch (player->getOrientation()) {
		case NORTH:
			angle = 270;
			break;
		case EAST:
			angle = 0;
			break;
		case SOUTH:
			angle = 90;
			break;
		case WEST:
			angle = 180;
			break;
		default:
			break;
	}
	player->getMesh()->setRotation(irr::core::vector3df(0, angle, 0));

}

void Scene::updatePlayerMovement(Map &map, Bot *player, irr::f32 timeUnit)
{
	irr::core::vector3df meshPos = player->getMesh()->getPosition();
	pos_t pos = player->getPos();
	pos_t oldPos = player->getOldPos();
	irr::s64 timeSinceMovement = std::chrono::duration_cast<std::chrono::milliseconds>(
		std::chrono::system_clock::now().time_since_epoch()
		- player->getLastMove().time_since_epoch()).count();
	irr::f32 status = timeSinceMovement * timeUnit / 2
		/ 1000 * timeUnit / 2;

	if (status >= 1 || (pos.x == oldPos.x && pos.y == oldPos.y)) {
		if (player->isMovement()) {
			player->getMesh()->setPosition(irr::core::vector3df(
				pos.x * map.getTilesize(),
				(irr::f32)(map.getTilesize() * 1.2),
				pos.y * (irr::f32)map.getTilesize() * -1));
			player->setMovement(false);
			player->setAnimation(irr::scene::EMAT_STAND);
		}
	}
	else {
		status = status > 1 ? 1 : status;
		status = 1 - status;
		auto start = irr::core::vector3df(oldPos.x * map.getTilesize(),
			meshPos.Y,
			oldPos.y * -1 * (irr::s32)map.getTilesize());
		auto end = start;
		if (meshPos == oldPos)
			player->setAnimation(irr::scene::EMAT_RUN);
		switch (player->getOrientation()) {
			case Orientation::WEST:
				end.X -= map.getTilesize();
				break;
			case Orientation::EAST:
				end.X += map.getTilesize();
				break;
			case Orientation::NORTH:
				end.Z += (irr::f32)map.getTilesize();
				break;
			case Orientation::SOUTH:
				end.Z -= map.getTilesize();
				break;
			default:
				break;
		}
		auto currentPos = start.getInterpolated(end, status);
		justifyPos(map, currentPos);
		player->getMesh()->setPosition(currentPos);
	}
}

void Scene::justifyPos(Map &map, irr::core::vector3df &pos)
{
	auto mapPos = pos;
	mapPos.X += map.getTilesize() / 2;
	mapPos.Z -= map.getTilesize() / 2;

	if (mapPos.X > map.getWidth())
		pos.X -= map.getWidth();
	if (mapPos.X < 0)
		pos.X += map.getWidth();
	if (mapPos.Z * -1 > map.getHeight())
		pos.Z += map.getHeight();
	if (mapPos.Z * -1 < 0)
		pos.Z -= map.getHeight();
}

void Scene::initPlayer(Map &map, std::unique_ptr<Bot> &bot)
{
	auto smgr = Window::device->getSceneManager();
	auto animatedMesh = smgr->getMesh(ResourceManager::getResPath(
		ResourceManager::PLAYER_MODEL).c_str());
	auto animatedMeshSceneNode = smgr->addAnimatedMeshSceneNode(animatedMesh);
	animatedMeshSceneNode->addShadowVolumeSceneNode();
	animatedMeshSceneNode->setMaterialType(irr::video::EMT_SOLID);
	animatedMeshSceneNode->setMaterialFlag(irr::video::EMF_NORMALIZE_NORMALS, true);
	animatedMeshSceneNode->setMaterialTexture(0,
		Window::device->getVideoDriver()->getTexture(
			ResourceManager::getResPath(
				ResourceManager::PLAYER_TEXTURE).c_str()));
	animatedMeshSceneNode->setPosition(irr::core::vector3df(
		bot.get()->getPos().x * map.getTilesize(),
		(irr::s32)(map.getTilesize() * 1.2),
		bot.get()->getPos().y * (irr::s32)map.getTilesize() * -1));
	animatedMeshSceneNode->setMD2Animation(irr::scene::EMAT_STAND);
	bot.get()->setMesh(animatedMeshSceneNode);
	auto level = smgr->addTextSceneNode(
		smgr->getGUIEnvironment()->getSkin()->getFont(),
		irr::core::stringw(bot.get()->getLevel()).c_str());
	level->setTextColor(getTeamColor(bot->getTeam()));
	bot.get()->setLevelLabel(level);
}

void Scene::initEgg(Map &map, std::unique_ptr<Egg> &egg)
{
	auto animatedMesh = Window::device->getSceneManager()->getMesh(
		ResourceManager::getResPath(ResourceManager::EGG_MODEL).c_str());
	auto animatedMeshSceneNode =
		Window::device->getSceneManager()->addAnimatedMeshSceneNode(animatedMesh);
	animatedMeshSceneNode->addShadowVolumeSceneNode();
	animatedMeshSceneNode->setMaterialType(irr::video::EMT_SOLID);
	animatedMeshSceneNode->setMaterialFlag(irr::video::EMF_NORMALIZE_NORMALS, true);
	animatedMeshSceneNode->setMaterialTexture(0,
		Window::device->getVideoDriver()->getTexture(
			ResourceManager::getResPath(
				ResourceManager::EGG_TEXTURE).c_str()));
	animatedMeshSceneNode->setPosition(irr::core::vector3df(
		egg.get()->getPos().x * map.getTilesize(),
		(irr::s32)(0),
		egg.get()->getPos().y * (irr::s32)map.getTilesize() * -1));
	animatedMeshSceneNode->setScale(irr::core::vector3df(20, 20, 20));
	egg.get()->setMesh(animatedMeshSceneNode);
}

void Scene::processEvents(Map &map)
{
	std::vector<std::pair<EventManager::Action, EventManager::InputType>>
		events = EventManager::getEvents();

	for (std::pair<EventManager::Action, EventManager::InputType> &event
		: events) {
		switch (event.first) {
			case EventManager::Action::SELECT:
				selectTile(map);
				break;
			case EventManager::Action::ZOOM_IN:
				cameraZoom(true);
				break;
			case EventManager::Action::ZOOM_OUT:
				cameraZoom(false);
				break;
			default:
				break;
		}
		if (event.first == EventManager::ROTATE)
			rotation = event.second == EventManager::PRESSED;
	}
	if (rotation)
		rotateCamera(map);
}

void Scene::selectTile(Map &map)
{
	irr::core::vector2d<irr::s32> mousePos = EventManager::getMousePos();
	irr::core::plane3d<irr::f32> ground(irr::core::vector3d<irr::f32>(0, 0, 0),
		irr::core::vector3d<irr::f32>(0, 1, 0));
	irr::core::line3df line = Window::device->getSceneManager()
		->getSceneCollisionManager()->getRayFromScreenCoordinates(mousePos, camera);
	irr::core::vector3df pos(0, 0, 0);
	deselectTile(map);
	if (ground.getIntersectionWithLimitedLine(line.start, line.end, pos)) {
		irr::core::vector2d<irr::s32> mapCoords(
			(irr::s32)((pos.X + map.getTilesize() * 0.5) / map.getTilesize()),
			(irr::s32)((pos.Z * -1 + map.getTilesize() * 0.5) / map.getTilesize()));
		if (mapCoords.X >= 0 && mapCoords.X < map.getSize().x
			&& mapCoords.Y >= 0 && mapCoords.Y < map.getSize().y) {
			pos.Y += map.getTilesize();
			map[mapCoords.Y][mapCoords.X]->getMesh()
				->setMaterialTexture(0,
				Window::device->getVideoDriver()->getTexture(
					"res/selectedFloor.jpg"));
			selectedPos = irr::core::vector2d<irr::s32>(mapCoords.X,
				mapCoords.Y);
		}
	}
}

void Scene::deselectTile(Map &map)
{

	for (unsigned int y = 0; y < map.getTiles().size(); y++) {
		for (unsigned int x = 0; x < map.getTiles()[0].size(); x++) {
			map[y][x]->getMesh()->setMaterialTexture(0,
				Window::device->getVideoDriver()->getTexture(
					"res/floor.jpg"));
		}
	}
	selectedPos = irr::core::vector2d<irr::s32>(-1, -1);
	hud.setUnselected();
}

void Scene::rotateCamera(Map &map)
{
	auto res = Window::device->getVideoDriver()->getViewPort();
	auto mousePos = EventManager::getMousePos();
	auto oldMousePos = EventManager::getOldMousePos();
	auto cameraPos = camera->getPosition();
	auto angle = irr::core::vector2df(
		(irr::f32)(oldMousePos.X - mousePos.X) / (res.getWidth() + 1) * 360,
		(irr::f32)(mousePos.Y - oldMousePos.Y) / (res.getHeight() + 1) * 270);

	auto mapCenter = irr::core::vector3df(map.getWidth() / 2,
		cameraPos.Y, (irr::s32)map.getHeight() / 2 * -1);
	cameraPos.rotateXZBy(angle.X, mapCenter);
	mapCenter = irr::core::vector3df(map.getWidth() / 2,
		0, (irr::s32)map.getHeight() / 2 * -1);
	cameraPos.rotateYZBy(angle.Y, mapCenter);
	camera->setPosition(cameraPos);
}

void Scene::cameraZoom(bool zoomIn)
{
	auto cameraPos = camera->getPosition();
	auto cameraTargetPos = camera->getTarget();

	if (zoomIn && cameraPos.getDistanceFrom(cameraTargetPos) > 50)
		camera->setPosition(cameraPos.getInterpolated(cameraTargetPos,
							0.9f));
	else if (cameraPos.getDistanceFrom(cameraTargetPos) < 500)
		camera->setPosition(cameraPos.getInterpolated(cameraTargetPos,
							1.1f));
}

void Scene::refreshDaylight(Map &map, int timeUnit)
{
	auto daytime = 60000 * 1 / (int)(timeUnit * 0.025 + 1);
	auto center = irr::core::vector3df(map.getWidth() / 2, 0,
		(irr::f32)map.getHeight() / 2 * -1);
	auto pos = irr::core::vector3df(center.X, map.getWidth(), center.Z);
	auto time = std::chrono::duration_cast<std::chrono::milliseconds>(
		std::chrono::system_clock::now().time_since_epoch()
		- start.time_since_epoch()).count() - (int)(daytime * 0.25);
	int status = (int)(((irr::f32)(time % daytime) / daytime) * 360);

	pos.rotateXYBy(status, center);
	dayLight->setPosition(pos);
}

const irr::video::SColor &Scene::getTeamColor(const std::string &team)
{
	if (!teamColors.count(team)) {
		teamColors[team] = colors[teamColors.size() % colors.size() - 1];
	}
	return teamColors[team];
}

bool operator==(const irr::core::vector3df &a, const pos_t &b)
{
	return (int)a.X / 20 == b.x && (int)(a.Z / 20 * -1) == b.y;
}