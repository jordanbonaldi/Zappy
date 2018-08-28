/*
** EPITECH PROJECT, 2018
** arcade
** File description:
** arcade
*/

#include <iostream>
#include "Player.hpp"

int main(int argc, char *argv[])
{
	std::string teamName;
	std::string machineName = "localhost";
	int port = 4242;
	int c;
	bool debug = false;

	while ((c = getopt (argc, argv, "p:n:h:d:")) != -1)
		switch (c)
		{
			case 'p':
				port = atoi(optarg);
				break;
			case 'n':
				teamName = optarg;
				break;
			case 'h':
				machineName = optarg;
				break;
			case 'd':
				debug = static_cast<bool>(atoi(optarg));
				break;
			default:
				printf("Invalid option -%c\n", c);
				break;
		}

	if (teamName.empty())
	{
		std::cerr << "You must enter team name" << std::endl;
		return 84;
	}

	srand(time(NULL));

	CommunicationHelper communicationHelper(port);

	if (!communicationHelper.connection(teamName))
		return 84;
	Player player(teamName, machineName, debug);
	player.connect(&communicationHelper);
	player.setArgv(argv[0], argv);
	player.play();
	return 0;
}
