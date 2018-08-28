/*
** EPITECH PROJECT, 2018
** client
** File description:
** client
*/

# ifndef DEFINITION_HH
	# define DEFINITION_HH

# define OBJECT_CREATOR(x, ...) typedef struct s_##x { \
				__VA_ARGS__; \
			} x;

# define OBJECT_DEFINE(x) typedef struct s_##x x;

/*
	Defining struct to allocating pre processing memory
*/

	OBJECT_DEFINE(User);
	OBJECT_DEFINE(Output);
	OBJECT_DEFINE(SockFile);
	OBJECT_DEFINE(Server);
	OBJECT_DEFINE(Buffer);
	OBJECT_DEFINE(Socket);
	OBJECT_DEFINE(LevelUp);
	OBJECT_DEFINE(CallBack);
	OBJECT_DEFINE(Channel);
	OBJECT_DEFINE(Input);
	OBJECT_DEFINE(Command);
	OBJECT_DEFINE(Client);
	OBJECT_DEFINE(Chan);
	OBJECT_DEFINE(Params);
	OBJECT_DEFINE(Team);
	OBJECT_DEFINE(Map);
	OBJECT_DEFINE(Tile);
	OBJECT_DEFINE(Ressource);
	OBJECT_DEFINE(Unknown);
	OBJECT_DEFINE(Rarity);
	OBJECT_DEFINE(GenerationRarity);
	OBJECT_DEFINE(ParamsInhibitor);
	OBJECT_DEFINE(Times);
	OBJECT_DEFINE(TimeManager);
	OBJECT_DEFINE(Queue);
	OBJECT_DEFINE(Container);
	OBJECT_DEFINE(Tests);

/*
	End pre processing definition
*/

OBJECT_CREATOR
(
	Unknown,

	void *alpha;
	void *beta;
);

# define sendGraphic(...) {\
			if (this->graphic) {\
				dprintf\
				(\
					this->graphic->index,\
					__VA_ARGS__\
				);\
			}\
		}

# define setUnknown(a, b) (Unknown) {\
				.alpha = a,\
				.beta = b\
			}

# define Status enum s_status

# define Direction enum s_Direction

# define String char *

# define _sendToUser(x, s) dprintf(x, s)

# define __sendToUser(user, s, ...) dprintf(user->index, s, __VA_ARGS__)

#endif
