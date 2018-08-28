/*
** EPITECH PROJECT, 2018
** connection
** File description:
** connection
*/

# ifndef LEVELUP_HH
	# define LEVELUP_HH

# include "server.h"

OBJECT_CREATOR
(
	LevelUp,

	int level;

	int players;

	Ressource *ressource;

	struct s_LevelUp *next;
)

# define getLevel(a) CALL_FUNCTION_PARAMS(getLevel, a)

# define setLvl(b, c, d) (LevelUp) {\
				.level = b,\
				.players = c,\
				.ressource = d,\
			}

# define createLvl(a, b, c, d, e, f, g, h) {\
				Ressource *$tmp = CALL_FUNCTION(loadItems);\
				getItem($tmp, "linemate")->nb = c;\
				getItem($tmp, "deraumere")->nb = d;\
				getItem($tmp, "sibur")->nb = e;\
				getItem($tmp, "mendiane")->nb = f;\
				getItem($tmp, "phiras")->nb = g;\
				getItem($tmp, "thystame")->nb = h;\
				LevelUp lvl = setLvl(a, b, $tmp);\
				CALL_FUNCTION_PARAMS(addLevel, lvl);\
			}

CREATE_FUNCTION(Ressource *, loadItems)
{
	__MALLOC_CR__(Ressource, ressource, sizeof(Ressource));

	ressource->items = NULL;

	linemateItem(ressource);
	deraumereItem(ressource);
	siburItem(ressource);
	mendianeItem(ressource);
	phirasItem(ressource);
	thystameItem(ressource);

	return ressource;
}

CREATE_FUNCTION_PARAMS(void, addLevel, LevelUp level)
{
	LevelUp *__lvl;
	LevelUp *tmp;

	__MALLOC__(__lvl, sizeof(Item));
	__lvl->level = level.level;
	__lvl->players = level.players;
	__lvl->ressource = level.ressource;
	__lvl->next = NULL;
	if (this->levels == NULL)
		this->levels = __lvl;
	else {
		tmp = this->levels;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = __lvl;
	}
}

CREATE_FUNCTION(void, initLevels)
{
	createLvl(2, 1, 1, 0, 0, 0, 0, 0);

	createLvl(3, 2, 1, 1, 1, 0, 0, 0);

	createLvl(4, 2, 2, 0, 1, 0, 2, 0);

	createLvl(5, 4, 1, 1, 2, 0, 1, 0);
	createLvl(6, 4, 1, 2, 1, 3, 0, 0);
	createLvl(7, 6, 1, 2, 3, 0, 1, 0);
	createLvl(8, 6, 2, 2, 2, 2, 2, 1);
}

CREATE_FUNCTION_PARAMS(LevelUp *, getLevel, int lvl)
{
	LevelUp *$lvl = NULL;

	FOREACH_LIST
	(
		LevelUp *,
		this->levels,
		{
			if (IT->level == lvl)
				$lvl = IT;
		}
	)
	__return($lvl)
}

CREATE_FUNCTION(void, destroyLevels)
{
	LevelUp *tmp = this->levels;
	LevelUp *tmp2 = this->levels;

	while (tmp) {
		tmp2 = tmp->next;
		CALL_FUNCTION_PARAMS(destructRessource, tmp->ressource);
		free(tmp);
		tmp = tmp2;
	}
}

CREATE_FUNCTION_PARAMS(bool, checkUpTile, Unknown unknown)
{
	LevelUp *lvl = unknown.alpha;
	Tile *tile = unknown.beta;
	int $i = 0;

	bool $allgood = true;

	FOREACH_LIST
	(
		ContainerPlayer *,
		tile->users,
		{
			if (!IT->user->dead && IT->user->hatched
				&& IT->user->level != lvl->level - 1)
				$allgood = false;

			if (!IT->user->dead && IT->user->hatched)
				$i++;
		}
	)

	if (lvl->players != $i)
		return false;

	FOREACH_LIST
	(
		Item *,
		tile->ressources->items,
		{
			if (!strcmp(IT->name, "food"))
				return;

			int nb = getItem(lvl->ressource, IT->name)->nb;

			if (nb != IT->nb)
				$allgood = false;
		}
	)

	if (tile->players != lvl->players)
		$allgood = false;
	if ($allgood) {
		FOREACH_LIST
		(
			Item *,
			tile->ressources->items,
			{
				if (!strcmp(IT->name, "food"))
					return;
				IT->nb = 0;
			}
		)
	}
	return $allgood;
}

# endif
