/*
** EPITECH PROJECT, 2018
** connection
** File description:
** connection
*/

# ifndef CONNECTOR_HH
	# define CONNECTOR_HH

# include "server.h"

CREATE_FUNCTION(void, bindListen)
{
	CALL_FUNCTION(bindEvent);

	CALL_FUNCTION(listenEvent);
}

CREATE_FUNCTION(void, connAddr)
{
	CALL_FUNCTION_PARAMS(setAddr, INADDR_ANY);
	
	CALL_FUNCTION(setSocketOption);
}

CREATE_FUNCTION(void, launchConnector)
{
	CALL_FUNCTION(initPreConnectionEvent);

	CALL_FUNCTION_PARAMS(setPort, this->params->port);
	CALL_FUNCTION(preConnectionEvent);

	CALL_FUNCTION(connAddr);

	CALL_FUNCTION(bindListen);

	CALL_FUNCTION(buildBuffer);

	setNULL(users);
	setNULL(cmds);
	setNULL(channels);
}

# endif
