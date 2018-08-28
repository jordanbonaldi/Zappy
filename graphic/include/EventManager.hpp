/*
** EPITECH PROJECT, 2018
** EventManager
** File description:
** Declaration of EventManager
*/

#ifndef PSU_ZAPPY_2017_EVENTMANAGER_HPP
	#define PSU_ZAPPY_2017_EVENTMANAGER_HPP

#include <irrlicht/irrlicht.h>
#include <vector>
#include <map>
#include "Event.hpp"

class EventManager
{
public:
	enum Action {
		MOVE_FORWARD,
		MOVE_BACKWARDS,
		MOVE_UP,
		MOVE_DOWN,
		MOVE_RIGHT,
		MOVE_LEFT,
		SELECT,
		ROTATE,
		ZOOM_IN,
		ZOOM_OUT
	};
	enum InputType {
		PRESSED,
		RELEASED
	};
	static void refresh(Event &event);
	static std::vector<std::pair<Action, InputType>> getEvents();
	static irr::core::vector2d<irr::s32> getMousePos();
	static const irr::core::vector2d<irr::s32> &getOldMousePos();
private:
	static std::vector<std::pair<Action, InputType>> events;
	static irr::core::vector2d<irr::s32> mousePos;
	static irr::core::vector2d<irr::s32> oldMousePos;

};


#endif //PSU_ZAPPY_2017_EVENTMANAGER_HPP
