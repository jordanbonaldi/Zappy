/*
** EPITECH PROJECT, 2018
** connection
** File description:
** connection
*/

# ifndef TEST_HH
	# define TEST_HH

# include "server.h"

# define MOCK_PLAYER User *user; {\
		addTeam("name");\
		this->params->width = 10;\
		this->params->height = 10;\
		CALL_FUNCTION_PARAMS(newUser, setUser(4));\
		user = this->users;\
		CALL_FUNCTION(createOutputAttributes);\
		CALL_FUNCTION(initFD);\
		this->output->selected = user;\
		CALL_FUNCTION_PARAMS(team, this->teams->name);\
		user->location->x = 5;\
		user->location->y = 5;\
	}

CREATE_TEST(test1)
{
	printf("hello world\n");
	return true;
}

CREATE_TEST(test2)
{
	this->params->width = 10;
	this->params->height = 10;

	BroadCast broadcast = setBroadCast
	(
		2, 9,
		5, 2,
		EAST
	);

	int res = CALL_FUNCTION_PARAMS(getBroadCast, broadcast);
	return res == 3;
}

CREATE_TEST(test3)
{
	this->params->width = 10;
	this->params->height = 10;

	BroadCast broadcast = setBroadCast
	(
		2, 1,
		9, 1,
		SOUTH
	);

	int res = CALL_FUNCTION_PARAMS(getBroadCast, broadcast);
	return res == 3;
}

CREATE_TEST(test4)
{
	this->params->width = 15;
	this->params->height = 15;

	BroadCast broadcast = setBroadCast
	(
		1, 1,
		1, 1,
		NORTH
	);

	int res = CALL_FUNCTION_PARAMS(getBroadCast, broadcast);
	return res == 0;
}

CREATE_TEST(test5)
{
	this->params->width = 15;
	this->params->height = 15;

	BroadCast broadcast = setBroadCast
	(
		2, 1,
		6, 1,
		NORTH
	);

	int res = CALL_FUNCTION_PARAMS(getBroadCast, broadcast);
	return res == 3;
}

CREATE_TEST(test6)
{
	this->params->width = 50;
	this->params->height = 50;

	BroadCast broadcast = setBroadCast
	(
		24, 23,
		38, 23,
		WEST
	);

	int res = CALL_FUNCTION_PARAMS(getBroadCast, broadcast);
	return res == 1;
}

CREATE_TEST(test7)
{
	this->params->width = 77;
	this->params->height = 32;

	BroadCast broadcast = setBroadCast
	(
		24, 17,
		24, 32,
		SOUTH
	);

	int res = CALL_FUNCTION_PARAMS(getBroadCast, broadcast);
	return res == 5;
}

CREATE_TEST(test8)
{
	this->params->width = 17;
	this->params->height = 56;

	BroadCast broadcast = setBroadCast
	(
		24, 23,
		24, 2,
		NORTH
	);

	int res = CALL_FUNCTION_PARAMS(getBroadCast, broadcast);
	return res == 5;
}

CREATE_TEST(test9)
{
	MOCK_PLAYER

	return getItem(user->ressources, "food")->nb == 11;
}

CREATE_TEST(test10)
{
	MOCK_PLAYER

	CALL_FUNCTION_PARAMS(setobject, "food");

	return getItem(user->ressources, "food")->nb == 10;
}

CREATE_TEST(test11)
{
	MOCK_PLAYER

	CALL_FUNCTION_PARAMS(takeobject, "food");

	return getItem(user->ressources, "food")->nb == 11;
}

CREATE_TEST(test12)
{
	MOCK_PLAYER

	user->location->direction = EAST;
	CALL_FUNCTION_PARAMS(move, NULL);

	return user->location->x == 6;
}

CREATE_TEST(test13)
{
	MOCK_PLAYER

	user->location->direction = WEST;
	CALL_FUNCTION_PARAMS(move, NULL);

	return user->location->x == 4;
}

CREATE_TEST(test14)
{
	MOCK_PLAYER

	user->location->direction = NORTH;
	CALL_FUNCTION_PARAMS(move, NULL);

	return user->location->y == 4;
}

CREATE_TEST(test15)
{
	MOCK_PLAYER

	user->location->direction = SOUTH;
	CALL_FUNCTION_PARAMS(move, NULL);

	return user->location->y == 6;
}

CREATE_TEST(test16)
{
	MOCK_PLAYER

	user->location->direction = SOUTH;
	CALL_FUNCTION_PARAMS(right, NULL);

	return user->location->direction == WEST;
}

CREATE_TEST(test17)
{
	MOCK_PLAYER

	user->location->direction = SOUTH;
	CALL_FUNCTION_PARAMS(left, NULL);

	return user->location->direction == EAST;
}

CREATE_TEST(test18)
{
	MOCK_PLAYER

	user->location->direction = SOUTH;
	CALL_FUNCTION_PARAMS(left, NULL);

	return !canI(_now_pl, user->time);
}

CREATE_TEST(test19)
{
	MOCK_PLAYER

	FOREACH_IT(50, {
		__SETUNUSED__(index)
		CALL_FUNCTION_PARAMS(setobject, "food");
	});

	return getItem(user->ressources, "food")->nb == 0;
}

CREATE_TEST(test20)
{
	int i = 0;
	this->params->freq = 1;
	Times *time = convert(42);
	i = (int)time->time->tv_sec;
	CALL_FUNCTION_PARAMS(destroyTime, time);
	return i == 42;
}

CREATE_TEST(test21)
{
	int i = 0;
	this->params->freq = 100;
	Times *time = convert(3000);
	i = (int)time->time->tv_sec;
	CALL_FUNCTION_PARAMS(destroyTime, time);
	return i == 30;
}

CREATE_TEST(test22)
{
	int i = 0;
	this->params->freq = 32;
	Times *time = convert(77);
	i = (int)time->time->tv_sec;
	CALL_FUNCTION_PARAMS(destroyTime, time);
	return i == 2;
}

INIT_TEST
{
	__ACTIVATED__("hello world", test1)
	__ACTIVATED__("broadcast across the map", test2)
	__ACTIVATED__("broadcast across the map", test3)
	__ACTIVATED__("broadcast same position", test4)
	__ACTIVATED__("broadcast right", test5)
	__ACTIVATED__("broadcast left", test6)
	__ACTIVATED__("broadcast bottom", test7)
	__ACTIVATED__("broadcast top", test8)
	__ACTIVATED__("initial food", test9)
	__ACTIVATED__("set command", test10)
	__ACTIVATED__("get command", test11)
	__ACTIVATED__("move EAST", test12)
	__ACTIVATED__("move WEST", test13)
	__ACTIVATED__("move NORTH", test14)
	__ACTIVATED__("move SOUTH", test15)
	__ACTIVATED__("turn right", test16)
	__ACTIVATED__("turn left", test17)
	__ACTIVATED__("time system check", test18)
	__ACTIVATED__("set too much command", test19)
	__ACTIVATED__("freq 1", test20)
	__ACTIVATED__("freq 100", test21)
	__ACTIVATED__("freq 32", test22)
}

# endif
