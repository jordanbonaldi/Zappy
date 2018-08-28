/*
** EPITECH PROJECT, 2018
** connection
** File description:
** connection
*/

# ifndef PARAMSHANDLER_HH
	# define PARAMSHANDLER_HH

# include "server.h"

OBJECT_CREATOR
(
	ParamsInhibitor,

	char param;

	int *pointer;

	struct s_ParamsInhibitor *next;
);

# define setArray(opt, obj) (ParamsInhibitor) { \
					.param = opt,\
					.pointer = &obj\
				}

#define addInhibitor(string, obj) \
			CALL_FUNCTION_PARAMS(addInhib, setArray(string, obj));

CREATE_FUNCTION_PARAMS(int *, getPointer, char p)
{
	int *obj = NULL;

	FOREACH_LIST
	(
		ParamsInhibitor *,
		this->params->opt,
		{
			if (IT->param == p)
				obj = IT->pointer;
		}
	);
	return obj;
}

CREATE_FUNCTION_PARAMS(bool, existsInhib, char p)
{
	bool exists = false;

	FOREACH_LIST
	(
		ParamsInhibitor *,
		this->params->opt,
		{
			if (IT->param == p)
				exists = true;
		}
	);
	return exists;
}

CREATE_FUNCTION_PARAMS(void, addInhib, ParamsInhibitor inhib)
{
	ParamsInhibitor *__cmd;
	ParamsInhibitor *tmp;
	__MALLOC__(__cmd, sizeof(ParamsInhibitor));

	__cmd->param = inhib.param;
	__cmd->pointer = inhib.pointer;
	__cmd->next = NULL;
	if (!this->params->opt)
		this->params->opt = __cmd;
	else {
		tmp = this->params->opt;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = __cmd;
	}
}

CREATE_FUNCTION(void, initParams)
{
	__MALLOC__(this->params, sizeof(Params));

	this->params->port = 4242;
	this->params->height = 10;
	this->params->width = 10;
	this->params->clientbyteam = 6;
	this->params->freq = 100;
	this->params->tests = 0;
	this->params->victory = 8;
	this->params->selecting_teams = false;
	setNULL(teams);
	setNULL(params->opt);

	addInhibitor('p', this->params->port);
	addInhibitor('y', this->params->height);
	addInhibitor('x', this->params->width);
	addInhibitor('c', this->params->clientbyteam);
	addInhibitor('f', this->params->freq);
	addInhibitor('t', this->params->tests);
	addInhibitor('v', this->params->victory);
}

CREATE_FUNCTION_PARAMS(int, getLength, String *args)
{
	__UNUSED__;
	__ATTR__(int, i);

	for (i = 0; args[i]; i++);

	return i;
}

CREATE_FUNCTION_PARAMS(void, loadParams, String *args)
{
	++args;
	CALL_FUNCTION(initParams);

	FOREACH_LENGTH
	(
		String,
		args,
		CALL_FUNCTION_PARAMS(getLength, args),
		{
			if (
				*IT == '-' &&
				CALL_FUNCTION_PARAMS(existsInhib, IT[1]) &&
				args[index + 1] &&
				!(this->params->selecting_teams = false)
			)
				*CALL_FUNCTION_PARAMS
				(
					getPointer,
					IT[1]
				) = atoi(args[index + 1]);
			else if (*IT == '-' && IT[1] == 'n')
				this->params->selecting_teams = true;

			if (this->params->selecting_teams && *IT != '-'
							&& !isdigit(*IT))
				addTeam(IT);
		}
	);

	printf("Port : %d\n", this->params->port);
}

CREATE_FUNCTION(void, destroyInhib)
{
	ParamsInhibitor *tmp = this->params->opt;
	ParamsInhibitor *tmp2;

	while (tmp) {
		tmp2 = tmp->next;
		free(tmp);
		tmp = tmp2;
	}
	free(this->params);
}

# endif
