/*
** EPITECH PROJECT, 2018
** Socket
** File description:
** Declaration of Socket
*/

#ifndef PSU_ZAPPY_2017_SOCKET_HPP
	#define PSU_ZAPPY_2017_SOCKET_HPP

#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <libgen.h>
#include <string>
#include <iostream>

class Socket
{
public:
	Socket(const char *ipAdress, int port);
	int create();
	int connection() const;
	int disconnection() const;
	int sendMessage(const std::string &string) const;
	std::string receiveMessage() const;
	int getFd() const;
private:
	const char *ipAdress;
	int port;
	int fd;
	struct sockaddr_in s_in;
};

#endif //PSU_ZAPPY_2017_SOCKET_HPP
