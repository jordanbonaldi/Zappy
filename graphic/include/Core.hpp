/*
** EPITECH PROJECT, 2018
** Core
** File description:
** Declaration of Core
*/

#ifndef PSU_ZAPPY_2017_CORE_HPP
#define PSU_ZAPPY_2017_CORE_HPP

#include "Socket.hpp"
#include "Commands.hpp"
#include "Data.hpp"

class Core {
public:
	Core(const char *ipAdress, int port);
	void init();
	void refresh();
	Data &getData();

private:
	Socket socket;
	int server_fd;
	fd_set fd_read;
	struct timeval tv;
	Data data;
};

#endif //PSU_ZAPPY_2017_CORE_HPP
