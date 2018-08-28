/*
** EPITECH PROJECT, 2018
** connection
** File description:
** connection
*/

# ifndef COMMANDS_HH
	# define COMMANDS_HH

# include "server.h"

# define player this->output->selected

# define _sendToConnected(s) dprintf(this->output->selected->index, s);

# define __sendToConnected(s, ...) dprintf(this->output->selected->index, s,\
								__VA_ARGS__);

# define __CUT__ { \
			if (strchr(args, ' ')) {\
				strtok(args, " ");\
				args = strtok(NULL, "");\
			}\
		}

# define __GRAPHIC__ \
			if (!args || !isdigit(*args)) {\
				_sendToConnected(H_SBP);\
				return;\
			}

# define XCALLER(entity, user, call, ...)	setCallBack\
			(\
				"NULL",\
				FUNC\
				(\
					void a(void *unknown)\
					{\
						entity *x = unknown;\
						__sendToUser\
						(\
							user,\
							call,\
							__VA_ARGS__,\
							getItem(x->ressources, "food")->nb,\
							getItem(x->ressources, "linemate")->nb,\
							getItem(x->ressources, "deraumere")->nb,\
							getItem(x->ressources, "sibur")->nb,\
							getItem(x->ressources, "mendiane")->nb,\
							getItem(x->ressources, "phiras")->nb,\
							getItem(x->ressources, "thystame")->nb\
						);\
					}\
				)\
			)

CREATE_FUNCTION_PARAMS(void, mct, String args)
{
	if (!args && !this->graphic)
		return;
	CALL_FUNCTION_PARAMS(actionOnTiles, XCALLER(
	Tile, (args ? player : this->graphic), H_BCT,
		x->x,
		x->y
	));
}

CREATE_FUNCTION_PARAMS(void, team, String args)
{
	Team *team = CALL_FUNCTION_PARAMS(getTeam, args);
	if (!team) {
		_sendToConnected(ERR_KO);
		player->msgs = 0;
		return;
	}
	if (team->reservedslot) {
		actionOnTeam
		(
			team,
			FUNC
			(
				void a(void *unknown)
				{
					User *_user = unknown;

					if (_user->layed) {
						_user->layed = false;
						player->time->refresh = true;
						player->isegg = true;
						player->newegg = true;
						player->egg = this->egg;
						player->hatched = false;

						/** TIME **/

							Times *_time = convert(600);

							addTimes(player->time, _time);

							CALL_FUNCTION_PARAMS(destroyTime, _time);

						/** END TIME **/

						CALL_FUNCTION_PARAMS(setOnMap,
						 	setUnknown(player, _user->location->tile));
					}
				}
			)
		)
	}
	CALL_FUNCTION_PARAMS(addPlayerInTeam, setUnknown(team, player));
	__sendToUser(player, "%d\n",
		CALL_FUNCTION_PARAMS(remainingPlayer, team));
	__sendToUser(player, "%d %d\n", this->params->width,
						this->params->height);
	team->reservedslot = false;
	CALL_FUNCTION_PARAMS(mct, NULL);
}

CREATE_FUNCTION_PARAMS(void, look, String args)
{
	User *user = player;
	CALL_FUNCTION_PARAMS(lookTile, setUnknown(user->location->tile, user));
}

CREATE_FUNCTION_PARAMS(void, right, String args)
{
	User *user = player;
	int a = 1;
	CALL_FUNCTION_PARAMS(changeDirection, setUnknown(user, &a));
	sendGraphic(H_PPO, player->index, player->location->x, player->location->y,
		getDirection(user->location->direction));
	_sendToConnected(DONE);
}

CREATE_FUNCTION_PARAMS(void, left, String args)
{
	User *user = player;
	int a = -1;
	CALL_FUNCTION_PARAMS(changeDirection, setUnknown(user, &a));
	sendGraphic(H_PPO, player->index, player->location->x, player->location->y,
		getDirection(user->location->direction));
	user->location->tile->print = 'p';
	//CALL_FUNCTION(printMap);
	user->location->tile->print = '.';
	_sendToConnected(DONE);
}

CREATE_FUNCTION_PARAMS(void, move, String args)
{
	User *user = player;

	CALL_FUNCTION_PARAMS(removePlayerInTile,
				setUnknown(player->location->tile, user));

	CALL_FUNCTION_PARAMS(moveUp, user);

	sendGraphic(H_PPO, player->index, player->location->x, player->location->y,
		getDirection(user->location->direction));

	_sendToConnected(DONE);
}

CREATE_FUNCTION_PARAMS(void, inventory, String args)
{
	User *user = player;

	_sendToConnected("[");
	CALL_FUNCTION_PARAMS(getInventoryContent,
		setUnknown(user->ressources, user));
	_sendToConnected("]\n");
}

CREATE_FUNCTION_PARAMS(void, unusedslot, String args)
{
	User *user = player;

	__sendToUser(user, "%d\n",
		CALL_FUNCTION_PARAMS(remainingPlayer, user->team));
}

CREATE_FUNCTION_PARAMS(void, fork, String args)
{
	player->laying = true;
	this->egg++;

	sendGraphic(H_PFK, player->index)
}

CREATE_FUNCTION_PARAMS(void, broadcast, String args)
{
	__CUT__

	CALL_FUNCTION_PARAMS
	(
		actOnPlayers,
		setCallBack
		(
			NULL,
			FUNC
			(
				void a(void *unknown)
				{
					User *user = unknown;
					if (
						!user
						|| !user->location
						|| !user->location->direction
						|| !user->location->tile
					)
						return;
					BroadCast broadcast = setBroadCast
					(
						player->location->x, player->location->y,
						user->location->x, user->location->y,
						user->location->direction
					);

					if (user->index == player->index)
						return;
					int calc = CALL_FUNCTION_PARAMS(getBroadCast, broadcast);
					__sendToUser(user, "message %d, %s\n", calc, args);
				}
			)
		)
	);
	_sendToConnected(DONE);
}

CREATE_FUNCTION_PARAMS(void, setobject, String args)
{
	__CUT__

	Tile *tile = player->location->tile;

	Item *_item = getItem(player->ressources, args);

	if (!_item) {
		_sendToConnected(ERR_KO);
		return;
	}

	Ressource *ressource = tile->ressources;

	if (getItem(player->ressources, _item->name)->nb <= 0) {
		_sendToConnected(ERR_KO);
		return;
	}

	CALL_FUNCTION_PARAMS
	(
		actionOnItems, setUnknown (
		ressource,
		&setCallBack
		(
			"NULL",
			FUNC
			(
				void a(void *it)
				{
					Item *item = it;

					if (!
						strcmp(item->name,
							_item->name)) {
						removeItem(item, _item);
						/* GRAPHIC SEND EXPULSION EVENTS */

							sendGraphic(H_PDR, player->index, _item->id);

							if (this->graphic) {
								CallBack callback = XCALLER(User,
									this->graphic, H_PIN,
									x->index,
									x->location->x,
									x->location->y
								);
								callback.action(player);

								callback = XCALLER(Tile,
									this->graphic, H_BCT,
									x->x,
									x->y
								);
								callback.action(tile);
							}

						/* --- */

					}
				}
			)
		)
	));
	_sendToConnected(DONE);
}

CREATE_FUNCTION_PARAMS(void, takeobject, String args)
{
	__CUT__

	Tile *tile = player->location->tile;

	Item *_item = getItem(player->ressources, args);

	if (!_item) {
		_sendToConnected(ERR_KO);
		return;
	}

	Ressource *ressource = tile->ressources;

	if (getItem(ressource, _item->name)->nb <= 0) {
		_sendToConnected(ERR_KO);
		return;
	}

	CALL_FUNCTION_PARAMS
	(
		actionOnItems, setUnknown (
		ressource,
		&setCallBack
		(
			"NULL",
			FUNC
			(
				void a(void *it)
				{
					Item *item = it;

					if (!strcmp(item->name,
						_item->name)) {
						removeItem(_item, item);
						/* GRAPHIC SEND EXPULSION EVENTS */

							sendGraphic(H_PGT, player->index, item->id);

							if (this->graphic) {
								CallBack callback = XCALLER(User,
									this->graphic, H_PIN,
									x->index,
									x->location->x,
									x->location->y
								);
								callback.action(player);

								callback = XCALLER(Tile,
									this->graphic, H_BCT,
									x->x,
									x->y
								);
								callback.action(tile);

							}

						/* --- */


					}
				}
			)
		)
	));
	_sendToConnected(DONE);
}

CREATE_FUNCTION_PARAMS(void, eject, String args)
{
	Tile *tile = player->location->tile;

	if (!tile) {
		_sendToConnected(ERR_KO);
		return;
	}

	ContainerPlayer *players = NULL;

	FOREACH_LIST
	(
		ContainerPlayer *,
		tile->users,
		{
			CALL_FUNCTION_PARAMS(addInContainer, setUnknown(players, IT));
		}
	)

	FOREACH_LIST
	(
		ContainerPlayer *,
		players,
		{
			if (!IT->user->dead && player->index != IT->user->index) {
				CALL_FUNCTION_PARAMS(removePlayerInTile,
							setUnknown(IT->user->location->tile, IT->user));

				CALL_FUNCTION_PARAMS(moveDown, IT->user);
				__sendToUser(IT->user, "eject: %s\n",
					getDirection(IT->user->location->direction));

				/* GRAPHIC SEND EXPULSION EVENTS */

					sendGraphic(H_PEX, IT->user->index)

				/* --- */
			}
		}
	)
	CALL_FUNCTION_PARAMS(destroyPlayerContainer, players);
	_sendToConnected(DONE);
}

CREATE_FUNCTION_PARAMS(void, incantation, String args)
{
	Tile *tile = player->location->tile;
	LevelUp *lvl = getLevel(player->level + 1);

	_sendToConnected(RUNNING_INCANTATION);
	sendGraphic(H_PIC, player->location->x, player->location->y, player->level + 1);
	FOREACH_LIST
	(
		ContainerPlayer *,
		tile->users,
		{
			sendGraphic(H_PIC_P, IT->user->index);
		}
	)
	sendGraphic(H_PIC_END);
	if (!lvl || !CALL_FUNCTION_PARAMS(checkUpTile, setUnknown(lvl, tile))) {
		player->enchanting = true;
		player->succeed = false;
		return;
	}

	player->enchanting = true;
	player->succeed = true;
	FOREACH_LIST
	(
		ContainerPlayer *,
		tile->users,
		{

			if (!IT->user->dead && IT->user->index != player->index) {
				Times *_time = convert(300);
				IT->user->time->refresh = true;
				addTimes(IT->user->time, _time);
				IT->user->enchanting = true;
				IT->user->succeed = true;
				CALL_FUNCTION_PARAMS(destroyTime, _time);
				_sendToUser(IT->user->index, RUNNING_INCANTATION);
			}
		}
	)
}

CREATE_FUNCTION_PARAMS(void, msz, String args)
{
	__sendToConnected(H_MSZ, this->params->width, this->params->height);
}

CREATE_FUNCTION_PARAMS(void, tna, String args)
{
	FOREACH_LIST
	(
		Team *,
		this->teams,
		{
			__sendToConnected(H_TNA, IT->name);
		}
	)
}

CREATE_FUNCTION_PARAMS(void, ppo, String args)
{
	__CUT__
	__GRAPHIC__

	User *user = CALL_FUNCTION_PARAMS(getUserByIndex, atoi(args));
	__sendToConnected
	(
		H_PPO,
		atoi(args),
		user->location->x,
		user->location->y,
		getDirection(user->location->direction)
	)
}

CREATE_FUNCTION_PARAMS(void, plv, String args)
{
	__CUT__
	__GRAPHIC__

	User *user = CALL_FUNCTION_PARAMS(getUserByIndex, atoi(args));
	__sendToConnected
	(
		H_PLV,
		atoi(args),
		user->level
	)
}

CREATE_FUNCTION_PARAMS(void, pin, String args)
{
	__CUT__
	__GRAPHIC__

	if (!args && !this->graphic)
		return;
	User *user = CALL_FUNCTION_PARAMS(getUserByIndex, atoi(args));
	CallBack callback = XCALLER(User,
		(args ? player : this->graphic), H_PIN,
		x->index,
		x->location->x,
		x->location->y
	);
	callback.action(user);
}

CREATE_FUNCTION_PARAMS(void, bct, String args)
{
	__CUT__
	__GRAPHIC__

	if (!args && !this->graphic)
		return;
	CallBack callback = XCALLER(Tile,
		(args ? player : this->graphic), H_BCT,
		x->x,
		x->y
	);

	int x = atoi(strtok(args, " "));
	int y = atoi(strtok(NULL, ""));
	Tile *tile = getTile(&x, &y);
	if (tile)
		callback.action(tile);
}

CREATE_FUNCTION_PARAMS(void, sgt, String args)
{
	__sendToConnected(H_SGT, this->params->freq);
}

CREATE_FUNCTION_PARAMS(void, sst, String args)
{
	__CUT__
	__GRAPHIC__

	this->params->freq = atoi(args);
	__sendToConnected(H_SST, this->params->freq);
}

CREATE_FUNCTION_PARAMS(void, graphic, String args)
{
	player->graphic = true;
	player->msgs++;
	this->graphic = player;
	CALL_FUNCTION_PARAMS(msz, NULL);
	CALL_FUNCTION_PARAMS(sgt, NULL);
	CALL_FUNCTION_PARAMS(mct, NULL);
	CALL_FUNCTION_PARAMS(tna, NULL);
	if (this->players > 0)
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
						if (user->graphic)
							return;
						if (user->newegg && !user->hatched) {
							sendGraphic
							(
								H_ENW,
								user->egg,
								user->index,
								user->location->x,
								user->location->y
							)
						} else
							sendGraphic
							(
								H_PNW,
								user->index,
								user->location->x,
								user->location->y,
								getDirection(user->location->direction),
								user->level,
								user->team->name
							)
					}
				)
			)
		);
}

# endif
