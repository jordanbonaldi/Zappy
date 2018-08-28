/*
** EPITECH PROJECT, 2018
** SocketClient
** File description:
** Declaration of SocketClient
*/

#ifndef NANOTEKSPICE_SOCKETCLIENT_HPP
	#define NANOTEKSPICE_SOCKETCLIENT_HPP

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

class SocketClient
{
public:
	SocketClient(const char *ipAdress, int port);
	int create();
	int connection() const;
	int disconnection() const;
	int sendMessage(const std::string &string) const;
	std::string receiveMessage() const;
private:
	const char *ipAdress;
	int port;
	int fd;
	struct sockaddr_in s_in;
};

#endif //NANOTEKSPICE_SOCKETCLIENT_HPP
