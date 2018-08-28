/*
** EPITECH PROJECT, 2018
** Controller
** File description:
** main
*/

#include <QApplication>
#include "Controller.hpp"

int main(int ac, char **av)
{
	QApplication app(ac, av);
	QCoreApplication::setOrganizationName("Casu Corp.");
	QCoreApplication::setApplicationName("Zappy");
	std::string teamName;
	std::string machineName = "localhost";
	int port = 4242;
	int c;
	bool debug = false;

	while ((c = getopt (ac, av, "p:n:h:d:")) != -1)
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

	Controller controller(teamName, machineName, debug);
	controller.connection(&communicationHelper);
	controller.setArgv(av[0], av);
	controller.show();
	return app.exec();
}