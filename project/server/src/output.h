/*
** EPITECH PROJECT, 2018
** connection
** File description:
** connection
*/

# ifndef OUTPUT_HH
	# define OUTPUT_HH

# include "server.h"

CREATE_FUNCTION(void, createOutputAttributes)
{
	__MALLOC__(this->output, sizeof(Output))
	this->output->index = -1;
	this->output->last = -1;
	this->output->selected = NULL;
}

CREATE_FUNCTION_PARAMS(void, callOne, bool first)
{
	if (first)
		CALL_FUNCTION(loadUser);
	else
		CALL_FUNCTION(readUser);
}

CREATE_FUNCTION(void, launchAction)
{
	FOREACH_IT(this->output->last + 1, {
		if (FD_ISSET(index, &this->output->read_fd)) {
			this->output->index = index;
			CALL_FUNCTION_PARAMS(callOne,
				index == this->socket->id);
		}
	});
}

CREATE_FUNCTION(void, destroyOutput)
{
	if (this->output)
		free(this->output);
}

CREATE_FUNCTION(void, initFD)
{
	FD_ZERO(&this->output->set);
	FD_SET(this->socket->id, &this->output->set);
	FD_ZERO(&this->output->read_fd);
}

CREATE_FUNCTION(void, waitingCommands)
{
	static _time_attr __time = 0;

	reload(_now_pl);
	__time++;
	CALL_FUNCTION_PARAMS
	(
		actOnPlayers,
		setCallBack
		(
			NULL,
			FUNC
			(
				void a(void *run)
				{
					User *user = run;

					if (user->dead)
						return;

					Item *food =
						user->msgs > 0
						? getItem(user->ressources, "food")
						: NULL;

					if (user->hatched && !(__time % 504) && food && food->nb > 0
						&& user->team && user->time &&
					canI(_now_pl, user->time))
					 	food->nb --;
					if (food && food->nb <= 0) {
						_sendToUser(user->index, "dead\n");
						CALL_FUNCTION_PARAMS(removeUser, user);
						return;
					}
					this->output->selected = user;
					if (user->enchanting && canI(_now_pl, user->time)) {
						user->enchanting = false;
						if (user->succeed) {
							user->level++;
							sendGraphic(H_PIE, user->location->x, user->location->y, user->level - 1);
							sendGraphic(H_PLV, user->index, user->level);
							__sendToUser(user, INCANTATION, user->level);
						} else {
							sendGraphic(H_PIE, user->location->x, user->location->y, 0);
							_sendToUser(user->index, ERR_KO);
						}
					} else if (user->laying && canI(_now_pl, user->time)) {
						user->laying = false;
						user->layed = true;
						user->team->reservedslot = true;
						sendGraphic
						(
							H_ENW,
							this->egg,
							player->index,
							player->location->x,
							player->location->y
						)
						_sendToConnected(DONE);
					} else if (user->newegg &&
						!user->hatched && canI(_now_pl, user->time)){
						user->hatched = true;
						sendGraphic(H_EHT, user->egg);
						sendGraphic(H_EBO, user->egg);
					}


					if (player->level == this->params->victory) {
						CALL_FUNCTION_PARAMS(winningTeam, player->team);
						return;
					}

					if (sizeQueue(user->queue->contained)
						&& canI(_now_pl, user->time))
						CALL_FUNCTION(getAnswer);
				}
			)
		)
	);
}

CREATE_FUNCTION(void, outputHandler)
{
	int ret = 0;
	CALL_FUNCTION(createOutputAttributes);
	CALL_FUNCTION(initFD);
	this->output->last = this->socket->id;
	while (true) {
		this->output->read_fd = this->output->set;
		ret = pselect(
			this->output->last + 1,
			&this->output->read_fd,
			NULL,
			NULL,
			this->time->timeout->time,
			NULL
		);
		if (!ret)
			CALL_FUNCTION(waitingCommands);
		CALL_FUNCTION(launchAction);
	}
}

# endif
