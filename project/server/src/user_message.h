/*
** EPITECH PROJECT, 2018
** connection
** File description:
** connection
*/

# ifndef USERMESSAGING_HH
	# define USERMESSAGING_HH

# include "server.h"

CREATE_FUNCTION_PARAMS(void, handleMessage, String response)
{
	String cut;

	reload(_now_io);
	while ((cut = strtok_r(response, "\n", &response))) {
		if (!player->msgs && (++player->msgs) &&
				strcmp("GRAPHIC", cut)) {
			CALL_FUNCTION_PARAMS(team, cut);
		} else if (canI(_now_io, player->time))
			CALL_FUNCTION_PARAMS(commandsHandler, strdup(cut));
	}
}

CREATE_FUNCTION(void, errOnReceive)
{
	CALL_FUNCTION_PARAMS(removeUser, this->output->selected);
}

CREATE_FUNCTION(void, getAnswer)
{
	String response = ((Queue *)player->queue->contained)->name;

	CALL_FUNCTION_PARAMS
	(
		handleMessage,
		response
	);

	CALL_FUNCTION_PARAMS(removeFirst,
				player->queue);
}

CREATE_FUNCTION(void, messagesHandler)
{
	char tmp[MAX_SIZE];
	String response = NULL;

	RESET(tmp, MAX_SIZE);
	if (recv(
		player->index,
		tmp,
		CALL_FUNCTION(getSizeLeft),
		0
	) > 0)
	{
		CALL_FUNCTION_PARAMS(writeDataBuffer, tmp);

		if (CALL_FUNCTION_PARAMS(getData, -1) == '\n') {
			if (!player->msgs) {
				response = CALL_FUNCTION(readDataBuffer);
				CALL_FUNCTION_PARAMS(handleMessage, response);
				free(response);
			} else
				addQueue(CALL_FUNCTION(readDataBuffer),
								player->queue);
		}
	} else
		CALL_FUNCTION(errOnReceive);
}

CREATE_FUNCTION(void, readUser)
{
	this->output->selected = CALL_FUNCTION_PARAMS(
					getUserByIndex,
					this->output->index
				);
	if (this->output->selected && this->output->selected->connected)
		CALL_FUNCTION(messagesHandler);
}

# endif
