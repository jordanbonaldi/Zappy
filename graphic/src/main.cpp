/*
** EPITECH PROJECT, 2018
** zappy_graphic
** File description:
** Main
*/

#include <iostream>
#include "Window.hpp"
#include "Core.hpp"

int main(int argc, char **argv)
{
	std::string machineName = "127.0.0.1";
	int port = 4242;
	int c;

	while ((c = getopt (argc, argv, "p:n:h:")) != -1) {
		switch (c)
		{
			case 'p':
				port = atoi(optarg);
				break;
			case 'h':
				machineName = optarg;
				break;
			default:
				printf("Invalid option -%c\n", c);
				break;
		}
	}

	Window window(machineName.c_str(), port);
	window.run();
	return 0;
}