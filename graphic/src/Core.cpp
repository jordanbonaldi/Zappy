/*
** EPITECH PROJECT, 2018
** Core
** File description:
** Implementation of Core
*/

#include "Core.hpp"

Core::Core(const char *ipAdress, int port)
	: socket(ipAdress, port)
{}

void Core::init()
{
	socket.create();
	socket.connection();
	server_fd = socket.getFd();
	socket.sendMessage("GRAPHIC\n");
}

void Core::refresh()
{
	std::string command;

	data.destroyDeadBots();
	data.destroyDeadEggs();

	tv.tv_sec = 0;
	tv.tv_usec = 200;
	FD_ZERO(&fd_read);
	FD_SET(server_fd, &fd_read);
	if (select(server_fd + 1, &fd_read, nullptr, nullptr, &tv) == -1)
		perror("select");
	if (FD_ISSET(server_fd, &fd_read)) {
		command = socket.receiveMessage();
		Commands::executeCommand(data, command);
	}
}

Data &Core::getData()
{
	return data;
}
