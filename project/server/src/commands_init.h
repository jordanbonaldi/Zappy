/*
** EPITECH PROJECT, 2018
** connection
** File description:
** connection
*/

# ifndef COMMANDS_REGISTER_HH
	# define COMMANDS_REGISTER_HH

# include "server.h"

CREATE_FUNCTION(void, registerCommands)
{
	/* USER COMMANDS */

		__add_cmd("Look", GET_FUNCTION(look), 7, false);
		__add_cmd("Right", GET_FUNCTION(right), 7, false);
		__add_cmd("Left", GET_FUNCTION(left), 7, false);
		__add_cmd("Forward", GET_FUNCTION(move), 7, false);
		__add_cmd("Set", GET_FUNCTION(setobject), 7, false);
		__add_cmd("Take", GET_FUNCTION(takeobject), 7, false);
		__add_cmd("Inventory", GET_FUNCTION(inventory), 1, false);
		__add_cmd("Connect_nbr", GET_FUNCTION(unusedslot), 0, false);
		__add_cmd("Eject", GET_FUNCTION(eject), 7, false);
		__add_cmd("Incantation", GET_FUNCTION(incantation), 300, false);
		__add_cmd("Fork", GET_FUNCTION(fork), 42, false);
		__add_cmd("Broadcast", GET_FUNCTION(broadcast), 7, false);

	/* GRAPHIC COMMANDS */

		__add_cmd("GRAPHIC", GET_FUNCTION(graphic), 0, false);

		__add_cmd("msz", GET_FUNCTION(msz), 0, true);

		__add_cmd("bct", GET_FUNCTION(bct), 0, true);

		__add_cmd("mct", GET_FUNCTION(mct), 0, true);

		__add_cmd("tna", GET_FUNCTION(tna), 0, true);

		__add_cmd("ppo", GET_FUNCTION(ppo), 0, true);

		__add_cmd("plv", GET_FUNCTION(plv), 0, true);

		__add_cmd("pin", GET_FUNCTION(pin), 0, true);

		__add_cmd("sgt", GET_FUNCTION(sgt), 0, true);

		__add_cmd("sst", GET_FUNCTION(sst), 0, true);

}

# endif
