/*
** EPITECH PROJECT, 2018
** connection
** File description:
** connection
*/

# ifndef USER_HH
	# define USER_HH

# include "server.h"

# define setUser(a) (User) {\
				.index = a,\
				.msgs = 0,\
				.level = 1,\
				.time = load,\
				.ressources = CALL_FUNCTION(createRessource)\
			}

CREATE_FUNCTION_PARAMS(void, setBuffer, User *user)
{
	this->buffer = user->buffer;
}

CREATE_FUNCTION(void, destroyUsers)
{
	User *tmp = this->users;
	User *tmp2;

	while (tmp) {
		tmp2 = tmp->next;
		free(tmp->location);
		CALL_FUNCTION_PARAMS(destroyQueue, tmp->queue);
		CALL_FUNCTION_PARAMS(destructRessource, tmp->ressources);
		CALL_FUNCTION_PARAMS(destroyTime, tmp->time);
		free(tmp);
		tmp = tmp2;
	}
}

CREATE_FUNCTION_PARAMS(void, newUser, User userinit)
{
	User *__user;
	User *tmp;

	__user = malloc(sizeof(User));
	__user->index = userinit.index;
	__user->ressources = userinit.ressources;
	__user->level = userinit.level;
	__user->msgs = userinit.msgs;
	__user->taketime = 0.0;
	__user->lastaction = 0;
	__user->time = userinit.time;
	__user->time->refresh = false;
	__user->team = NULL;
	__user->enchanting = false;
	__user->graphic = false;
	__user->laying = false;
	__user->layed = false;
	__user->isegg = false;
	__user->newegg = false;
	__user->egg = 0;
	__user->dead = false;
	__user->succeed = false;
	__user->hatched = true;
	__user->queue = malloc(sizeof(Container));
	__user->queue->contained = NULL;
	getItem(__user->ressources, "food")->nb = 11;
	__MALLOC__(__user->location, sizeof(Location))
	__user->location->tile = NULL;
	__user->next = NULL;
	__user->connected = true;
	__user->setBuffer = GET_FUNCTION(setBuffer);
	if (this->users == NULL)
		this->users = __user;
	else {
		tmp = this->users;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = __user;
	}
}

CREATE_FUNCTION_PARAMS(void, unLinkIndex, int index)
{
	FD_CLR(index, &this->output->set);
	close(index);
}

CREATE_FUNCTION(void, setUserFd)
{
	FD_SET
	(
		this->socket->connected_fd,
		&this->output->set
	);
}

CREATE_FUNCTION_PARAMS(void, removeUser, User *user)
{
	/* GRAPHIC PLAYER DEATH EVENT */

		if (!user->graphic && !user->egg && user->team)
			sendGraphic(H_PDI, user->index)
		else if (!user->graphic && user->team) {
			if (!user->hatched) {
				sendGraphic(H_EHT, user->egg);
				sendGraphic(H_EBO, user->egg);
			}
			sendGraphic(H_EDI, user->egg)
		}

	/* --- */

	if (!this->graphic)
		this->players--;
	user->dead = true;
	CALL_FUNCTION_PARAMS(unLinkIndex, user->index);
	if (user->location->tile)
		CALL_FUNCTION_PARAMS(removePlayerInTile, setUnknown(user->location->tile, user));
	if (user->team)
		CALL_FUNCTION_PARAMS(removePlayerInTeam, user);
}

CREATE_FUNCTION(void, loadUser)
{
	CALL_FUNCTION(acceptEvent);
	CALL_FUNCTION_PARAMS(
		newUser,
		setUser
		(
			this->socket->connected_fd
		)
	);
	_sendToUser(this->socket->connected_fd, "WELCOME\n");
	CALL_FUNCTION(setUserFd);
	if (this->socket->connected_fd > this->output->last)
		this->output->last = this->socket->connected_fd;
}

# endif
