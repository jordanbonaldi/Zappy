/*
** EPITECH PROJECT, 2018
** connection
** File description:
** connection
*/

# ifndef RESSOURCES_HH
	# define RESSOURCES_HH

# include "server.h"

OBJECT_CREATOR
(
	Item,

	String name;

	int nb;

	int id;

	GenerationRarity generationrarity;

	struct s_Item *next;
);

OBJECT_CREATOR
(
	Ressource,

	Item *items;
);

# define removeItem(i1, i2) {\
				i1->nb += i2->nb > 0 ? 1 : 0;\
				i2->nb = i2->nb > 0 ? i2->nb - 1 : 0;\
			}

# define setItem(a, b, gmi, gma, grt, i) (Item) {\
				.name = a,\
				.nb = b,\
				.id = i,\
				.generationrarity = \
					setGenerationRarity(gmi, gma, grt),\
				.next = NULL\
			}

# define cloneItem(main, i) \
				CALL_FUNCTION_PARAMS\
				(\
					newItem,\
					setUnknown\
					(\
						main,\
						i\
					)\
				)\

# define addItem(main, name, nb, gmi, gma, grt, gid) \
			CALL_FUNCTION_PARAMS\
			(		newItem, \
					setUnknown\
					(\
						main, \
						&(setItem \
						(\
							name, \
							nb,\
							gmi,\
							gma,\
							grt,\
							gid\
						))\
					)\
				)

# define getItem(main, name) CALL_FUNCTION_PARAMS(getItem, \
					setUnknown\
					(\
						main,\
						name\
					)\
				)

# define getItemByRarity(main, rarity) CALL_FUNCTION_PARAMS(getItemByRarity, \
					setUnknown\
					(\
						main,\
						rarity\
					)\
				)

# define getItemByIndex(main, index) CALL_FUNCTION_PARAMS(getItemByIndex,\
						setUnknown\
						(\
							main,\
							&index\
						)\
					)

CREATE_FUNCTION_PARAMS(void, newItem, Unknown unknown)
{
	Item *__item;
	Item *tmp;

	__MALLOC__(__item, sizeof(Item));
	__item->name = ((Item *)unknown.beta)->name;
	__item->nb = ((Item *)unknown.beta)->nb;
	__item->id = ((Item *)unknown.beta)->id;
	__item->generationrarity = ((Item *)unknown.beta)->generationrarity;
	__item->next = NULL;
	if (((Ressource *)unknown.alpha)->items == NULL)
		((Ressource *)unknown.alpha)->items = __item;
	else {
		tmp = ((Ressource *)unknown.alpha)->items;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = __item;
	}
}

CREATE_FUNCTION_PARAMS(int, getSizeOfItems, Item **item)
{
	register int i = 0;

	while (item[i])
	{
		i++;
	}
	return i;
}

CREATE_FUNCTION_PARAMS(Item *, getItemByIndex, Unknown unknown)
{
	Item *item = NULL;
	int $i = 0;

	_get(Item, _item, alpha)
	_get(int, _index, beta)

	FOREACH_LIST
	(
		Item *,
		_item,
		{
			if (*_index == $i)
				item = IT;
			$i++;
		}
	)
	return item;
}

CREATE_FUNCTION_PARAMS(Item *, getItemByRarity, Unknown unknown)
{
	_get(Ressource, ressource, alpha)
	_get(Rarity, rarity, beta)
	__MALLOC_CR__(Item *, $_item_array, sizeof(Item *) * 4);
	int $i = 0;

	FOREACH_LIST
	(
		Item *,
		ressource->items,
		{
			if (IT->generationrarity.rarity.rarity ==
				(*rarity).rarity)
				$_item_array[$i++] = IT;
		}
	)
	$_item_array[$i] = NULL;
	Item *it = NULL;
	int size = CALL_FUNCTION_PARAMS(getSizeOfItems, $_item_array);
	if (size > 1) {
		int random = (rand() % ((size - 1) + 1));
		it = $_item_array[random];
	} else
		it = *$_item_array;
	free($_item_array);
	return it;
}

CREATE_FUNCTION_PARAMS(Item *, getItem, Unknown unknown)
{
	Item *item = NULL;

	FOREACH_LIST
	(
		Item *,
		((Ressource *)unknown.alpha)->items,
		{
			if (!strcmp(IT->name, (String)unknown.beta))
				item = IT;
		}
	);
	return item;
}

CREATE_FUNCTION_PARAMS(void, actionOnItems, Unknown unknown)
{
	_get(Ressource, ressources, alpha)
	_get(CallBack, callback, beta)

	FOREACH_LIST
	(
		Item *,
		ressources->items,
		{
			callback->action(IT);
		}
	)
}

CREATE_FUNCTION(Ressource *, createRessource)
{
	__MALLOC_CR__(Ressource, ressource, sizeof(Ressource));

	ressource->items = NULL;

	linemateItem(ressource);
	deraumereItem(ressource);
	foodItem(ressource);
	siburItem(ressource);
	mendianeItem(ressource);
	phirasItem(ressource);
	thystameItem(ressource);

	return ressource;
}

CREATE_FUNCTION_PARAMS(void, destructRessource, Ressource *ressource)
{
	Item *tmp = ressource->items;
	Item *tmp2;

	while (tmp) {
		tmp2 = tmp->next;
		free(tmp);
		tmp = tmp2;
	}
	free(ressource);
}

CREATE_FUNCTION_PARAMS(void, getXContent, Unknown unknown)
{
	Item *item = (Item *)unknown.alpha;
	User *user = (User *)unknown.beta;

	char string[(int)strlen(item->name) * (item->nb * 2)];

	RESET(string, (int)strlen(item->name) * (item->nb * 2));

	for (int i = 0; i < item->nb; i++)
		strcat(strcat(string, item->name), " ");

	__sendToUser(user, "%s", string);
}

CREATE_FUNCTION_PARAMS(void, getRessourceContent, Unknown unknown)
{
	Ressource *ressource = (Ressource *)unknown.alpha;
	User *user = (User *)unknown.beta;

	FOREACH_LIST
	(
		Item *,
		ressource->items,
		{
			if (IT->nb > 0) {
				CALL_FUNCTION_PARAMS
				(
					getXContent,
					setUnknown
					(
						getItem
						(
							ressource,
							IT->name
						),
						user
					)
				);
			}
		}
	);
}

# endif
