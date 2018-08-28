/*
** EPITECH PROJECT, 2018
** EventManager
** File description:
** Implementation of EventManager
*/

#include <iostream>
#include "EventManager.hpp"


std::vector<std::pair<EventManager::Action, EventManager::InputType>> EventManager::events;
irr::core::vector2d<irr::s32> EventManager::mousePos;
irr::core::vector2d<irr::s32> EventManager::oldMousePos;

static std::map<irr::EKEY_CODE, EventManager::Action> actions = {
	{ irr::KEY_UP, EventManager::Action::MOVE_FORWARD },
	{ irr::KEY_LEFT, EventManager::Action::MOVE_LEFT },
	{ irr::KEY_DOWN, EventManager::Action::MOVE_BACKWARDS },
	{ irr::KEY_RIGHT, EventManager::Action::MOVE_RIGHT },
	{ irr::KEY_PRIOR, EventManager::Action::MOVE_UP },
	{ irr::KEY_NEXT, EventManager::Action::MOVE_DOWN },
	{ irr::KEY_LBUTTON, EventManager::Action::SELECT},
	{ irr::KEY_RBUTTON, EventManager::Action::ROTATE},
};

void EventManager::refresh(Event &event)
{
	events.clear();
	for (auto &line : actions) {
		if (event.isKeyDown(line.first))
			events.push_back({line.second, PRESSED});
		else if (event.isKeyReleased(line.first))
			events.push_back({line.second, RELEASED});
	}
	auto mouseWheel = event.getMouseWheel();
	if (mouseWheel > 0)
		events.push_back({EventManager::ZOOM_IN, PRESSED});
	else if (mouseWheel < 0)
		events.push_back({EventManager::ZOOM_OUT, PRESSED});
	mousePos = event.getMousePos();
	oldMousePos = event.getOldMousePos();
}

std::vector<std::pair<EventManager::Action, EventManager::InputType>>
EventManager::getEvents()
{
	return events;
}

irr::core::vector2d<irr::s32> EventManager::getMousePos()
{
	return mousePos;
}

const irr::core::vector2d<irr::s32> &EventManager::getOldMousePos()
{
	return oldMousePos;
}