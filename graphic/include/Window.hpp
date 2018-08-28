/*
** EPITECH PROJECT, 2018
** Window
** File description:
** Declaration of Window
*/

#ifndef PSU_ZAPPY_2017_WINDOW_HPP
	#define PSU_ZAPPY_2017_WINDOW_HPP

#include <irrlicht/irrlicht.h>
#include "Scene.hpp"
#include "Core.hpp"
#include "Event.hpp"

class Window
{
public:
	Window(const char *ipAdress, int port);
	~Window() = default;
	void run();
	static Event event;
	static irr::IrrlichtDevice *device;
private:
	Scene scene;
	Core core;
};

#endif //PSU_ZAPPY_2017_WINDOW_HPP
