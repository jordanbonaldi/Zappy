/*
** EPITECH PROJECT, 2018
** connection
** File description:
** connection
*/

# ifndef TILE_HH
	# define TILE_HH

# include "server.h"

# define getDirection(x) CALL_FUNCTION_PARAMS(getDirection, x)

OBJECT_CREATOR
(
	ContainerPlayer,

	User *user;

	struct s_ContainerPlayer *next;
);

OBJECT_CREATOR
(
	Tile,

	ContainerPlayer *users;

	int x;

	int y;

	char print;

	short players;

	Ressource *ressources;
);

CREATE_FUNCTION_PARAMS(void, generateContent, Ressource *ressource)
{
	int randomnb = (rand() % 100) + 1;
	Rarity rarity = CALL_FUNCTION_PARAMS(getRarity, randomnb);
	Item *item = getItemByRarity(ressource, &rarity);
	item->nb = (rand() %
		(item->generationrarity.max
			- item->generationrarity.min + 1)
			+ item->generationrarity.min);
}

CREATE_FUNCTION_PARAMS(void, launchGenerators, Tile *tile)
{
	int randomnb = (rand() % 10);
	for (int i = 0; i < randomnb; i++) {
		CALL_FUNCTION_PARAMS(generateContent, tile->ressources);
		CALL_FUNCTION_PARAMS(generateContent, tile->ressources);
		CALL_FUNCTION_PARAMS(generateContent, tile->ressources);
	}
	getItem(tile->ressources, "food")->nb = 15;
}

CREATE_FUNCTION_PARAMS(Tile *, newTile, Unknown unknown)
{
	__MALLOC_CR__(Tile, tile, sizeof(Tile));

	tile->ressources = CALL_FUNCTION(createRessource);

	tile->users = NULL;

	tile->print = '.';

	tile->players = 0;

	tile->x = *(int *)unknown.alpha;
	tile->y = *(int *)unknown.beta;

	CALL_FUNCTION_PARAMS(launchGenerators, tile);
	return tile;
}

CREATE_FUNCTION_PARAMS(void, addPlayerInTile, Unknown unknown)
{
	Tile *tile = (Tile *)unknown.alpha;
	User *user = (User *)unknown.beta;
	ContainerPlayer *__user;
	ContainerPlayer *tmp;

	__user = malloc(sizeof(ContainerPlayer));
	tile->players ++;
	__user->user = user;
	__user->next = NULL;
	if (tile->users == NULL)
		tile->users = __user;
	else {
		tmp = tile->users;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = __user;
	}
}

CREATE_FUNCTION_PARAMS(void, removePlayerInTile, Unknown unknown)
{
	_get(Tile, tile, alpha)
	_get(User, user, beta)

	ContainerPlayer *tmp = tile->users;
	ContainerPlayer *tmp2 = NULL;

	tile->players --;
	if (!tile->players || !getItem(tile->ressources, "food")->nb)
		CALL_FUNCTION_PARAMS(launchGenerators, tile);
	if (tmp && tmp->user == user) {
		if (!tmp->next) {
			free(tile->users);
			tile->users = NULL;
		} else {
			tmp2 = tmp->next;
			free(tmp);
			tile->users = tmp2;
		}
		return;
	}
	while (tmp->next) {
		if (tmp->next->user->index == user->index)
			break;
		tmp = tmp->next;
	}
	tmp2 = tmp->next->next;
	free(tmp->next);
	tmp->next = tmp2;
}

CREATE_FUNCTION_PARAMS(void, destroyPlayerContainer, ContainerPlayer *players)
{
	ContainerPlayer *tmp = players;
	ContainerPlayer *tmp2 = NULL;

	while (tmp) {
		tmp2 = tmp->next;
		free(tmp);
		tmp = tmp2;
	}
}

CREATE_FUNCTION_PARAMS(void, destructTile, Tile *tile)
{
	CALL_FUNCTION_PARAMS(destructRessource, tile->ressources);
	CALL_FUNCTION_PARAMS(destroyPlayerContainer, tile->users);
	free(tile);
}

CREATE_FUNCTION_PARAMS(void, getPlayerContent, Unknown unknown)
{
	ContainerPlayer *players = (ContainerPlayer *)unknown.alpha;
	User *user = (User *)unknown.beta;

	FOREACH_LIST
	(
		ContainerPlayer *,
		players,
		{
			if (IT &&
				IT->user &&
				user &&
				IT->user->hatched) {
				__sendToUser
				(
					user,
					"%s%s",
					"player",
					(IT->next ? " " : "")
				);
			}
		}
	);
}

CREATE_FUNCTION_PARAMS(void, getTileContent, Unknown unknown)
{
	Tile *tile = (Tile *)unknown.alpha;

	CALL_FUNCTION_PARAMS(getRessourceContent,
		setUnknown(tile->ressources, unknown.beta));

	CALL_FUNCTION_PARAMS(getPlayerContent,
		setUnknown(tile->users, unknown.beta));
}

CREATE_FUNCTION_PARAMS(String, getDirection, Direction direction)
{
	switch (direction) {
		case NORTH:
			return "1";
		case WEST:
			return "4";
		case SOUTH:
			return "3";
		case EAST:
			return "2";
	}
	return "NONE";
}

# endif
