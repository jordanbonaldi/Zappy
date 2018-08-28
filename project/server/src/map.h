/*
** EPITECH PROJECT, 2018
** connection
** File description:
** connection
*/

# ifndef MAP_HH
	# define MAP_HH

# include "server.h"

OBJECT_CREATOR
(
	TileContainer,

	Tile *tile;

	struct s_TileContainer *next;
)

OBJECT_CREATOR
(
	Map,

	Tile ** *tile;
);

# define getTile(x, y) CALL_FUNCTION_PARAMS(getTile, setUnknown(x, y))

# define addTile(container, x, y) CALL_FUNCTION_PARAMS(addTileInContainer, \
						setUnknown(getTile(&x, &y), \
								container));

CREATE_FUNCTION(void, initTiles)
{
	__MALLOC__
	(
		this->map->tile,
		sizeof(Tile) * this->params->height * this->params->width
	);

	for (int i = 0; i < this->params->height; i++) {
		__MALLOC__
		(
			this->map->tile[i],
			this->params->width * sizeof(Tile)
		);

		for (int j = 0; j < this->params->width; j++)
			this->map->tile[i][j] =
				CALL_FUNCTION_PARAMS
				(
					newTile,
					setUnknown(&j, &i)
				);
	}
}

CREATE_FUNCTION(void, destructMap)
{
	for (int i = 0; i < this->params->height; i++) {
		for (int j = 0; j < this->params->width; j++)
			CALL_FUNCTION_PARAMS
			(
				destructTile,
				this->map->tile[i][j]
			);
		free(this->map->tile[i]);
	}
	free(this->map->tile);
	free(this->map);
}

CREATE_FUNCTION_PARAMS(void, actionOnTiles, CallBack callback)
{
	for (int i = 0; i < this->params->height; i++) {
		for (int j = 0; j < this->params->width; j++)
			callback.action(this->map->tile[i][j]);
	}
}

CREATE_FUNCTION_PARAMS(Tile *, getTile, Unknown unknown)
{
	int x = *(int *)unknown.alpha, y = *(int*)unknown.beta;

	if (x >= this->params->width)
		x %= this->params->width;
	while (x < 0)
		x += this->params->width;

	if (y >= this->params->height)
		y %= this->params->height;
	while (y < 0)
		y += this->params->height;

	return this->map->tile[y][x];
}

CREATE_FUNCTION(void, initMap)
{
	__MALLOC__(this->map, sizeof(Map));
	CALL_FUNCTION(initTiles);
}

CREATE_FUNCTION_PARAMS(void, setOnMap, Unknown unknown)
{
	User *user = (User *)unknown.alpha;
	Tile *tile = (Tile *)unknown.beta;

	user->location->x = tile->x;
	user->location->y = tile->y;
	user->location->tile = tile;

	CALL_FUNCTION_PARAMS(addPlayerInTile, setUnknown(tile, user));
}

CREATE_FUNCTION_PARAMS(void, putOnMap, User *user)
{
	int x = rand() % this->params->width;
	int y = rand() % this->params->height;

	Tile *tile = this->map->tile[y][x];

	CALL_FUNCTION_PARAMS(setOnMap, setUnknown(user, tile));
}

CREATE_FUNCTION_PARAMS(void, addTileInContainer, Unknown unknown)
{
	Tile *tile = (Tile *)unknown.alpha;
	TileContainer *__user;
	TileContainer *tmp;

	tile->print = 'x';

	__user = malloc(sizeof(TileContainer));
	__user->tile = tile;
	__user->next = NULL;
	if (*(TileContainer **)unknown.beta == NULL)
		*(TileContainer **)unknown.beta = __user;
	else {
		tmp = *(TileContainer **)unknown.beta;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = __user;
	}
}

CREATE_FUNCTION_PARAMS(void, destroyTileContainer, TileContainer *container)
{
	TileContainer *tmp = container;
	TileContainer *tmp2;

	while (tmp) {
		tmp2 = tmp->next;
		tmp->tile->print = '.';
		free(tmp);
		tmp = tmp2;
	}
}

CREATE_FUNCTION_PARAMS(void, sendTiles, Unknown unknown)
{
	TileContainer *container = (TileContainer *)unknown.alpha;
	User *user = (User *)unknown.beta;

	_sendToUser(user->index, "[");
	FOREACH_LIST
	(
		TileContainer *,
		container,
		{
			CALL_FUNCTION_PARAMS(getTileContent,
					setUnknown(IT->tile, user));
			if (IT->next)
				_sendToUser(user->index, ",");
		}
	);
	_sendToUser(user->index, "]\n");
}

CREATE_FUNCTION_PARAMS(void, lookTile, Unknown unknown)
{
	Tile *tile = (Tile *)unknown.alpha;
	User *user = (User *)unknown.beta;
	Direction direction = user->location->direction;
	int level = user->level;
	TileContainer *container = NULL;

	CALL_FUNCTION_PARAMS(addTileInContainer, setUnknown(tile, &container));

	for (int i = 0; i < level; i++) {
		for (int j = 0; j < 1 + ((i + 1) * 2); j++) {
			int x =
				direction == NORTH ? tile->x - (i + 1) + j :
				direction == SOUTH ? tile->x + (i + 1) - j :
				direction == WEST ? tile->x - (i + 1) :
				tile->x + (i + 1);
			int y =
				direction == NORTH ? tile->y - i - 1 :
				direction == SOUTH ? tile->y + i + 1 :
				direction == WEST ? tile->y + (i + 1) - j :
				tile->y - (i + 1) + j;
			addTile
			(
				&container,
				x,
				y
			);
		}
	}
	CALL_FUNCTION_PARAMS(sendTiles, setUnknown(container, user));
	CALL_FUNCTION_PARAMS(destroyTileContainer, container);
}

# endif
