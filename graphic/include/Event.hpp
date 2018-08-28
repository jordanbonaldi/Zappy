/*
** EPITECH PROJECT, 2018
** Event
** File description:
** Declaration of Event
*/

#ifndef PSU_ZAPPY_2017_EVENT_HPP
	#define PSU_ZAPPY_2017_EVENT_HPP

#include <irrlicht/irrlicht.h>

class Event : public irr::IEventReceiver
{
public:
	Event();
	bool OnEvent(const irr::SEvent &event) override;
	bool isKeyDown(irr::EKEY_CODE keyCode) const;
	bool isKeyReleased(irr::EKEY_CODE keyCode);
	irr::core::vector2d<irr::s32> getMousePos() const;
	void setMousePos(const irr::core::vector2d<irr::s32> &mousePos);
	const irr::core::vector2d<irr::s32> &getOldMousePos() const;
	irr::f32 getMouseWheel();

private:
	bool keyIsDown[irr::KEY_KEY_CODES_COUNT];
	bool keyIsReleased[irr::KEY_KEY_CODES_COUNT];
	irr::core::vector2d<irr::s32> mousePos;
	irr::core::vector2d<irr::s32> oldMousePos;
	irr::f32 mouseWheel;
};


#endif //PSU_ZAPPY_2017_EVENT_HPP
