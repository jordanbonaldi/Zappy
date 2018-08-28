/*
** EPITECH PROJECT, 2018
** connection
** File description:
** connection
*/

# ifndef TEAMSHANDLER_HH
	# define TEAMSHANDLER_HH

# include "server.h"

OBJECT_CREATOR
(
	Team,

	String name;

	int current;

	bool full;

	int max;

	ContainerPlayer *teamplayers;

	bool reservedslot;

	struct s_Team *next;

);

# define setTeam(string) (Team) { \
					.name = string,\
				}

# define addTeam(name) \
		CALL_FUNCTION_PARAMS(addTeam, setTeam(name));

# define actionOnTeam(t, f) CALL_FUNCTION_PARAMS\
			(\
				actionOnTeamPlayers,\
				setUnknown\
				(\
					t,\
					&setCallBack\
					(\
						NULL,\
						f\
					)\
				)\
			);

CREATE_FUNCTION_PARAMS(void, actionOnTeamPlayers, Unknown unknown)
{
	_get(Team, team, alpha)
	_get(CallBack, callback, beta)

	FOREACH_LIST
	(
		ContainerPlayer *,
		team->teamplayers,
		{
			if (IT && IT->user && !IT->user->dead)
				callback->action(IT->user);
		}
	)
}

CREATE_FUNCTION_PARAMS(Team *, getTeam, String name)
{
	Team *obj = NULL;

	FOREACH_LIST
	(
		Team *,
		this->teams,
		{
			if (!strcmp(name, IT->name))
				obj = IT;
		}
	)
	return obj;
}

CREATE_FUNCTION_PARAMS(void, addTeam, Team team)
{
	Team *__cmd;
	Team *tmp;
	__MALLOC__(__cmd, sizeof(Team));

	__cmd->name = team.name;
	__cmd->current = 0;
	__cmd->max = this->params->clientbyteam;
	__cmd->teamplayers = NULL;
	__cmd->reservedslot = false;
	__cmd->next = NULL;
	if (!this->teams)
		this->teams = __cmd;
	else {
		tmp = this->teams;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = __cmd;
	}
}

CREATE_FUNCTION_PARAMS(int, remainingPlayer, Team *team)
{
	return team->max - team->current;
}

CREATE_FUNCTION_PARAMS(void, setIfFull, Team *team)
{
	if (CALL_FUNCTION_PARAMS(remainingPlayer, team) <= 0)
		team->full = true;
	team->full = false;
}

CREATE_FUNCTION_PARAMS(void, addPlayerInTeam, Unknown unknown)
{
	Team *team = (Team *)unknown.alpha;
	User *user = (User *)unknown.beta;
	ContainerPlayer *__user;
	ContainerPlayer *tmp;

	__user = malloc(sizeof(ContainerPlayer));
	int dir = rand() % 4;

	user->location->direction = dir;

	if (!user->isegg)
		CALL_FUNCTION_PARAMS(putOnMap, user);

	/* NEW CONNECTION SENT TO GRAPHIC CLIENTS */

		sendGraphic
		(
			H_PNW,
			user->index,
			user->location->x,
			user->location->y,
			getDirection(user->location->direction),
			user->level,
			team->name
		)

	/* --- */


	team->current ++;
	this->players ++;
	user->team = team;
	CALL_FUNCTION_PARAMS(setIfFull, team);
	__user->user = user;
	__user->next = NULL;
	if (team->current == 1)
		team->teamplayers = __user;
	else {
		tmp = team->teamplayers;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = __user;
	}
}

CREATE_FUNCTION_PARAMS(void, removePlayerInTeam, User *user)
{
	Team *team = user->team;

	ContainerPlayer *tmp = team->teamplayers;
	ContainerPlayer *tmp2 = NULL;

	team->current --;
	if (!team->current) {
		free(team->teamplayers);
		team->teamplayers = NULL;
		return;
	} else if (tmp && tmp->user == user) {
		if (!tmp->next) {
			free(team->teamplayers);
			team->teamplayers = NULL;
		} else {
			tmp2 = tmp->next;
			free(tmp);
			team->teamplayers = tmp2;
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

CREATE_FUNCTION(void, destroyTeams)
{
	Team *tmp = this->teams;
	Team *tmp2;

	while (tmp) {
		tmp2 = tmp->next;
		CALL_FUNCTION_PARAMS(destroyPlayerContainer, tmp->teamplayers);
		free(tmp);
		tmp = tmp2;
	}
}

CREATE_FUNCTION_PARAMS(void, winningTeam, Team *team)
{
	sendGraphic(H_SEG, team->name);
	printf("Winning team : %s\n", team->name);
	sleep(10);
	CALL_FUNCTION_LINKED(__EXIT);
}

# endif
