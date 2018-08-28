/*
** EPITECH PROJECT, 2018
** Event
** File description:
** Implementation of Event
*/

#include "Event.hpp"

Event::Event() : mousePos(0, 0), oldMousePos(0, 0)
{
	for (irr::u32 i = 0; i < irr::KEY_KEY_CODES_COUNT; ++i) {
		keyIsDown[i] = false;
		keyIsReleased[i] = false;
	}
}

bool Event::OnEvent(const irr::SEvent& event)
{
	if (event.EventType == irr::EET_KEY_INPUT_EVENT) {
		keyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
		keyIsReleased[event.KeyInput.Key] = !event.KeyInput.PressedDown;
		return true;
	}
	else if (event.EventType == irr::EET_MOUSE_INPUT_EVENT)
	{
		keyIsDown[irr::KEY_LBUTTON] = false;
		keyIsDown[irr::KEY_RBUTTON] = false;
		keyIsReleased[irr::KEY_LBUTTON] = false;
		keyIsReleased[irr::KEY_RBUTTON] = false;
		switch (event.MouseInput.Event)
		{
			case irr::EMIE_LMOUSE_PRESSED_DOWN:
				keyIsDown[irr::KEY_LBUTTON] = true;
				break;
			case irr::EMIE_RMOUSE_PRESSED_DOWN:
				keyIsDown[irr::KEY_RBUTTON] = true;
				break;
			case irr::EMIE_LMOUSE_LEFT_UP:
				keyIsReleased[irr::KEY_LBUTTON] = true;
				break;
			case irr::EMIE_RMOUSE_LEFT_UP:
				keyIsReleased[irr::KEY_RBUTTON] = true;
				break;
			case irr::EMIE_MOUSE_MOVED:
				setMousePos(irr::core::vector2d<irr::s32>(
					event.MouseInput.X, event.MouseInput.Y));
				break;
			case irr::EMIE_MOUSE_WHEEL:
				mouseWheel = event.MouseInput.Wheel;
				break;
			default:
				break;
		}
	}
	return false;
}

bool Event::isKeyReleased(irr::EKEY_CODE keyCode)
{
	if (keyIsReleased[keyCode]) {
		keyIsReleased[keyCode] = false;
		return true;
	}
	return false;
}

bool Event::isKeyDown(irr::EKEY_CODE keyCode) const
{
	return keyIsDown[keyCode];
}

void Event::setMousePos(const irr::core::vector2d<irr::s32> &mousePos)
{
	oldMousePos = Event::mousePos;
	Event::mousePos = mousePos;
}

irr::core::vector2d<irr::s32> Event::getMousePos() const
{
	return mousePos;
}

const irr::core::vector2d<irr::s32> &Event::getOldMousePos() const
{
	return oldMousePos;
}

irr::f32 Event::getMouseWheel()
{
	auto ret = mouseWheel;
	mouseWheel = 0.0;
	return ret;
}

