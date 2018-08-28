/*
** EPITECH PROJECT, 2018
** SERVER
** File description:
** SERVER
*/

# ifndef SERVER_HH
	# define SERVER_HH

# define SERVER

# include <sys/select.h>
# include <stdbool.h>

# include "definition.h"

# define MAIN_PREFIX server

# define MAIN_STRUCT Server

OBJECT_CREATOR
(
	Params,

	int port;
	int height;
	int width;
	int clientbyteam;
	int freq;
	int tests;
	int victory;

	/* PARAMS ARRAY */

		bool selecting_teams;

		ParamsInhibitor *opt;

	/* END PARAMLS ARRAY */
);

OBJECT_CREATOR
(
	Server,

	/** OBJECT PARAMS **/

		Command *cmds;
		Channel *channels;
		Output *output;
		Socket *socket;
		Buffer *buffer;
		User *users;
		User *graphic;
		Team *teams;
		LevelUp *levels;
		Params *params;
		Map *map;
		TimeManager *time;
		Tests *tests;

	/** END OBJ **/

	/** GENERAL ATTRIBUTES **/

		int players;

		int egg;

	/** END ATTRIBUTES **/

);

OBJECT_CREATOR
(
	Output,

	fd_set read_fd;
	fd_set set;

	int index;
	int last;

	User *selected;
);

enum s_Direction
{
	NORTH,
	EAST,
	SOUTH,
	WEST
};

OBJECT_CREATOR
(
	Location,

	int x;
	int y;

	Direction direction;

	Tile *tile;
);

OBJECT_CREATOR
(
	User,

	/* GRAPHIC CLIENT */

		bool graphic;

	/* CORE ATTRIBUTES */

		int index;
		int msgs;
		bool connected;

		Times *time;

		Buffer *buffer;

		Container *queue;

		void (*setBuffer)(MAIN_STRUCT *, struct s_User *);

		struct s_User *next;

	/* END CORE ATTRIBUTES */

	/* EGG ATTRIBUTES */

		bool laying;

		bool layed;

		bool isegg;

		bool newegg;

		int egg;

		bool hatched;

	/* END EGG ATTRIBUTES */

	/* TIMING ATTRIBUTES */

		unsigned long lastaction;

		bool enchanting;

		bool succeed;

		float taketime;

	/* END TIMING ATTRIBUTES */

	/* GAME ATTRIBUTES */

		Ressource *ressources;

		Location *location;

		Team *team;

		bool dead;

		short level;

	/* END GAME ATTRIBUTES */

);

void __EXIT(MAIN_STRUCT *);

//

// LOADING HANDLERS

		# include "project.h"

// LOADING RESSOURCES (need to load them separately for conflicts)

	// IN COMMON RESSOURCES

		# include "buffer.h"

	// IN SERVER

		# include "rarity.h"
		# include "ressources.h"
		# include "tile.h"
		# include "map.h"
		# include "team_handler.h"
		# include "params_handler.h"
		# include "broadcast.h"
		# include "levelup.h"
		# include "user_managements.h"
		# include "commands_queue.h"
		# include "commands.h"
		# include "commands_manager.h"
		# include "commands_init.h"
		# include "user.h"
		# include "user_message.h"
		# include "output.h"
		# include "connector.h"
		# include "test.h"

CREATE_FUNCTION_NEUTRAL_LINKED(void, __EXIT)
{
	printf("\nClosing connection\n");
	CALL_FUNCTION(destroyConnection);
	CALL_FUNCTION(destructMap);
	CALL_FUNCTION(destroyOutput);
	CALL_FUNCTION(deleteBuffer);
	CALL_FUNCTION(destroyUsers);
	CALL_FUNCTION(destroyCommands);
	CALL_FUNCTION(destroyTeams);
	CALL_FUNCTION(destroyInhib);
	CALL_FUNCTION(destroyTimeManager);
	CALL_FUNCTION(destroyLevels);
	CALL_FUNCTION(destroyTests);
	exit(EXIT_SUCCESS);
}

CREATE_MAIN(int, main)
{
	MAIN_STRUCT this;

	srand(time(NULL));
	signal(SIGINT, FUNC(void a(int sig) {
		__SETUNUSED__(sig);
		printf("Stopping server\n");
		CALL_FUNCTION_LINKED_PASSED(__EXIT);
	}));

	this.graphic = NULL;
	this.players = 0;
	this.egg = 0;
	this.tests = NULL;

	/* PARAMETERS + TEAM LOADING */

		CALL_FUNCTION_PARAMS_AS_PASS(loadParams, argv);

	/* CONNECTION */

		CALL_FUNCTION_AS_PASS(launchConnector);

	/* INIT COMMANDS */

		CALL_FUNCTION_AS_PASS(registerCommands);

	/* INIT MAP */

		CALL_FUNCTION_AS_PASS(initMap);

	/* INIT TIME MANAGER */

		this.time = CALL_FUNCTION_AS_PASS(setTimeManager);

	/* INIT LEVELS */

		this.levels = NULL;
		CALL_FUNCTION_AS_PASS(initLevels);

	/* TESTS HANDLERS */

		if (this.params->tests) {

			printf("\n\n\nTESTING MODE ACTIVATED\n\n\n");

			CALL_FUNCTION_AS_PASS(init_test);
			CALL_FUNCTION_AS_PASS(launchTests);

			CALL_FUNCTION_LINKED_PASSED(__EXIT);

			return 0;
		}

	/* READ ( select ) Infinite loop */

		CALL_FUNCTION_AS_PASS(outputHandler);

	return 0;
}

#endif
