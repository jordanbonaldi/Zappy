/*
** EPITECH PROJECT, 2018
** HUD
** File description:
** Implementation of HUD
*/

#include "Window.hpp"
#include "ResourceManager.hpp"
#include "HUD.hpp"

HUD::HUD()
{
	irr::gui::IGUIEnvironment *env = Window::device->getGUIEnvironment();
	irr::video::IVideoDriver *driver = Window::device->getVideoDriver();
	auto res = driver->getViewPort();
	std::vector<std::pair<std::string, irr::core::stringw>> items = {
		{ResourceManager::getResPath(ResourceManager::FOOD_ICON), "Food"},
		{ResourceManager::getResPath(ResourceManager::GEM_YELLOW_ICON), "Linemate"},
		{ResourceManager::getResPath(ResourceManager::GEM_GREEN_ICON), "Deraumere"},
		{ResourceManager::getResPath(ResourceManager::GEM_RED_ICON), "Sibur"},
		{ResourceManager::getResPath(ResourceManager::GEM_WHITE_ICON), "Mendiane"},
		{ResourceManager::getResPath(ResourceManager::GEM_BLUE_ICON), "Phiras"},
		{ResourceManager::getResPath(ResourceManager::GEM_PURPLE_ICON), "Thystame"},
	};

	env->getSkin()->setFont(env->getFont(ResourceManager::getResPath(
		ResourceManager::FONT).c_str()));
	parent = env->addWindow(irr::core::rect<irr::s32>(
		(irr::s32)(res.getWidth() * 0.1),
		(irr::s32)(res.getHeight() * 0.7),
		(irr::s32)(res.getWidth() * 0.9),
		res.getHeight()));
	parent->getCloseButton()->setVisible(false);
	parent->setDraggable(false);
	parent->setDrawTitlebar(false);
	res = parent->getAbsolutePosition();
	for (int i = 0; i < 7; i++) {
		auto rect = irr::core::rect<irr::s32>(
			(irr::s32)(res.getWidth() * 0.6 + (i > 3 ? 100 : 0)),
			(irr::s32)(res.getHeight() * 0.15 + 30 * (i % 4)),
			(irr::s32)(res.getWidth() * 0.6 + (i > 3 ? 130 : 30)),
			(irr::s32)(res.getHeight() * 0.15 + 30 * (i % 4 + 1)));
		auto icon = env->addImage(rect, parent);
		icon->setImage(driver->getTexture(items[i].first.c_str()));
		icon->setUseAlphaChannel(true);
		icon->setScaleImage(true);
		icon->setToolTipText(items[i].second.c_str());
		auto rect2 = irr::core::rect<irr::s32>(
			rect.LowerRightCorner.X,
			rect.UpperLeftCorner.Y,
			rect.LowerRightCorner.X + 100,
			rect.LowerRightCorner.Y);
		auto text = env->addStaticText(L"0", rect2, false, true,
			parent);
		resources.push_back({icon, text});
	}
	speed = env->addStaticText(L"Game speed: 0",
		irr::core::rect<irr::s32>(
			(irr::s32)(res.getWidth() * 0.05),
			(irr::s32)(res.getHeight() * 0.15),
			(irr::s32)(res.getWidth() * 0.5),
			(irr::s32)(res.getHeight() * 0.15 + 40)), false, true,
		parent);
	teamsNb = env->addStaticText(L"Teams number: 0",
		irr::core::rect<irr::s32>(
			(irr::s32)(res.getWidth() * 0.05),
			(irr::s32)(res.getHeight() * 0.15 + 45),
			(irr::s32)(res.getWidth() * 0.5),
			(irr::s32)(res.getHeight() * 0.15 + 85)), false, true,
		parent);
	playersNb = env->addStaticText(L"Players count: 0",
		irr::core::rect<irr::s32>(
			(irr::s32)(res.getWidth() * 0.05),
			(irr::s32)(res.getHeight() * 0.15 + 90),
			(irr::s32)(res.getWidth() * 0.5),
			(irr::s32)(res.getHeight() * 0.15 + 130)), false, true,
		parent);
	noSelection = env->addStaticText(L"No tile selected",
		irr::core::rect<irr::s32>(
			(irr::s32)(res.getWidth() * 0.5),
			(irr::s32)(res.getHeight() * 0.40),
			(irr::s32)(res.getWidth()),
			(irr::s32)(res.getHeight() * 0.60)), false, true,
		parent);
	noSelection->setTextAlignment(irr::gui::EGUIA_CENTER,
		irr::gui::EGUIA_CENTER);
}

void HUD::refresh(Data &data)
{
	auto &bots = data.getBots();
	std::vector<std::string> teams;

	for (auto &bot : bots) {
		if (std::find(teams.begin(),
			teams.end(),bot.get()->getTeam()) == teams.end())
			teams.emplace_back(bot.get()->getTeam());
	}
	speed->setText((irr::core::stringw("Game speed: ")
		+ irr::core::stringw((int)data.getTimeUnit())).c_str());
	teamsNb->setText((irr::core::stringw("Teams number: ")
		+ irr::core::stringw(teams.size())).c_str());
	playersNb->setText((irr::core::stringw("Players count: ")
		+ irr::core::stringw(data.getBots().size())).c_str());
}

void HUD::setSelected(Tile &tile)
{
	ResourcesNb content = tile.getResourcesQuantity();

	noSelection->setVisible(false);
	for (unsigned int i = 0; i < resources.size(); i++) {
		resources[i].first->setVisible(true);
		resources[i].second->setVisible(true);
		resources[i].second->setText(
			irr::core::stringw(content[(Resource::Type)i]).c_str());
	}
}

void HUD::setUnselected()
{
	noSelection->setVisible(true);
	for (unsigned int i = 0; i < resources.size(); i++) {
		resources[i].first->setVisible(false);
		resources[i].second->setVisible(false);
	}
}