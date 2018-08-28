/*
** EPITECH PROJECT, 2018
** connection
** File description:
** connection
*/

# ifndef USERMOVEMENT_HH
	# define USERMOVEMENT_HH

# include "server.h"

CREATE_FUNCTION_PARAMS(User *, getUserByIndex, int index)
{
	User *obj = NULL;

	FOREACH_LIST
	(
		User *,
		this->users,
		{
			if (!IT->dead && IT->index == index)
				obj = IT;
		}
	)
	return obj;
}

CREATE_FUNCTION_PARAMS(void, addInContainer, Unknown unknown)
{
	_get(ContainerPlayer, container, alpha)
	_get(User, user, beta)

	ContainerPlayer *__user;
	ContainerPlayer *tmp;

	__user = malloc(sizeof(ContainerPlayer));
	__user->user = user;
	if (!container)
		container = __user;
	else {
		tmp = container;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = __user;
	}
}

CREATE_FUNCTION_PARAMS(void, changeDirection, Unknown unknown)
{
	User *user = (User *)unknown.alpha;
	int dir = *(int *)unknown.beta;

	if (dir == -1 && (user->location->direction == 0))
		user->location->direction = 3;
	else {
		user->location->direction += dir;
		if (user->location->direction > 3)
			user->location->direction = 0;
	}
}

CREATE_FUNCTION_PARAMS(void, moveUp, User *user)
{
	int x = user->location->x;
	int y = user->location->y;

	Tile *newtile = NULL;
	Direction direction = user->location->direction;

	x += direction == WEST ? -1 :
		direction == EAST ? 1 : 0;

	y += direction == NORTH ? -1 :
		direction == SOUTH ? 1 : 0;

	newtile = getTile
		(
			&x,
			&y
		);
	CALL_FUNCTION_PARAMS(setOnMap, setUnknown(user, newtile));
}

CREATE_FUNCTION_PARAMS(void, moveDown, User *user)
{
	int x = user->location->x;
	int y = user->location->y;

	Tile *newtile = NULL;
	Direction direction = user->location->direction;

	x += direction == EAST ? -1 :
		direction == WEST ? 1 : 0;

	y += direction == NORTH ? 1 :
		direction == SOUTH ? -1 : 0;

	newtile = getTile
		(
			&x,
			&y
		);
	CALL_FUNCTION_PARAMS(setOnMap, setUnknown(user, newtile));
}

CREATE_FUNCTION_PARAMS(void, getInventoryContent, Unknown unknown)
{
	Ressource *ressource = (Ressource *)unknown.alpha;
	User *user = (User *)unknown.beta;

	FOREACH_LIST
	(
		Item *,
		ressource->items,
		{
			__sendToUser(user, "%s %d", IT->name, IT->nb);
			if (IT->next)
				_sendToUser(user->index, ", ");
		}
	);
}

CREATE_FUNCTION_PARAMS(void, actOnPlayers, CallBack callback)
{
	FOREACH_LIST
	(
		User *,
		this->users,
		{
			if (!IT->dead && this->players > 0) {
				callback.action(IT);
			}
		}
	);
}

# endif
