/*
** EPITECH PROJECT, 2018
** Window
** File description:
** Implementation of Window
*/

#include <EventManager.hpp>
#include "Window.hpp"

Event Window::event;

irr::IrrlichtDevice *Window::device = irr::createDevice(irr::video::EDT_OPENGL,
	irr::core::dimension2du(800, 600), 16,
	false, true, true, &event);

Window::Window(const char *ipAdress, int port) : scene(), core(ipAdress, port)
{
	core.init();
}

void Window::run()
{
	int lastFPS = -1;

	while (device->run()) {
		device->getVideoDriver()->beginScene(true, true,
			irr::video::SColor(255, 0, 0, 0));
		EventManager::refresh(event);
		scene.refresh(core.getData());
		int fps = device->getVideoDriver()->getFPS();
		if (lastFPS != fps) {
			irr::core::stringw str(L"CasuCorp FPS: ");
			str += fps;
			device->setWindowCaption(str.c_str());
			lastFPS = fps;
		}
		core.refresh();
		device->getVideoDriver()->endScene();
	}
}