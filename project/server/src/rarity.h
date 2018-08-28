/*
** EPITECH PROJECT, 2018
** connection
** File description:
** connection
*/

# ifndef RARITY_HH
	# define RARITY_HH

# include "project.h"

OBJECT_CREATOR
(
	Rarity,

	int in;
	int out;

	int rarity;
);

OBJECT_CREATOR
(
	GenerationRarity,

	/* GENERATIONS MAX AND MIN */

		int max;
		int min;

	/* END GENERATION DECLARATIONS */

	/* RARITY OF OBJECT */

		Rarity rarity;

	/* END RARITY */

);


# define setRarity(i, o, r) (Rarity) {\
				.in = i,\
				.out = o,\
				.rarity = r\
			}

Rarity _LOW = setRarity(60, 100, 9);
Rarity _NORMAL = setRarity(40, 59, 6);
Rarity _HIGH = setRarity(20, 39, 4);
Rarity _CRITICAL = setRarity(0, 19, 2);

# define getRarities Rarity rarities[] = {_LOW, _NORMAL, _HIGH, _CRITICAL}

CREATE_FUNCTION_PARAMS(Rarity, getRarity, int random)
{
	Rarity rarity;
	getRarities;

	FOREACH_LENGTH
	(
		Rarity,
		rarities,
		4,
		{
			__SETUNUSED__(index);
			if (random >= IT.in && random <= IT.out)
				rarity = IT;
		}
	);

	return rarity;
}

# define setGenerationRarity(mi, ma, rt) (GenerationRarity) {\
						.min = mi,\
						.max = ma,\
						.rarity = rt\
					}

/* LINEMATE ITEM DECLARATION */

# define linemateItem(main) addItem(main, "linemate", 0, 1, 8, _LOW, 1)

/* DERAUMERE ITEM DECLARATION */

# define deraumereItem(main) addItem(main, "deraumere", 0, 1, 7, _LOW, 2)

/* FOOD ITEM DECLARATION */

# define foodItem(main) addItem(main, "food", 0, 2, 15, _LOW, 0)

/* SIBUR ITEM DECLARATION */

# define siburItem(main) addItem(main, "sibur", 0, 1, 6, _NORMAL, 3)

/* MENDIANE ITEM DECLARATION */

# define mendianeItem(main) addItem(main, "mendiane", 0, 1, 4, _HIGH, 4)

/* PHIRAS ITEM DECLARATION */

# define phirasItem(main) addItem(main, "phiras", 0, 1, 4, _HIGH, 5)

/* THUSTAME ITEM DECLARATION */

# define thystameItem(main) addItem(main, "thystame", 0, 1, 4, _CRITICAL, 6)

# endif
