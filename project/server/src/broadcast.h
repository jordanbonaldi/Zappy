/*
** EPITECH PROJECT, 2018
** connection
** File description:
** connection
*/

# ifndef BROADCAST_HH
	# define BROADCAST_HH

# include "project.h"

#define _abs(x)  ( ( (x) < 0) ? -(x) : (x) )

OBJECT_CREATOR
(
	BroadCast,

	int x1;
	int x2;
	int y1;
	int y2;
	Direction dir;
)

# define setBroadCast(x, y, xb, yb, d) (BroadCast) {\
						.x1 = x,\
						.x2 = xb,\
						.y1 = y,\
						.y2 = yb,\
						.dir = d,\
					}

CREATE_FUNCTION_PARAMS(int, calcCorrection, BroadCast broadcast)
{
	int correction = 0;

	switch (broadcast.dir) {
		case NORTH:
			correction = -2;
			break;
		case WEST:
			correction = -4;
			break;
		case SOUTH:
			correction = 2;
			break;
		default:
			correction = 0;
			break;
	}
	return correction;
}

CREATE_FUNCTION_PARAMS(int, process_calcul, BroadCast broadcast)
{
	float x1 = broadcast.x1;
	float x2 = broadcast.x2;
	float y1 = broadcast.y1;
	float y2 = broadcast.y2;

	float a = 0;
	float mapX = this->params->width;
	float mapY = this->params->height;
	float diffX = _abs(x1 - x2);
	if (diffX > (mapX / 2)) {
		diffX = _abs(_abs(x1 - x2) - (mapX + 1));
		x2 = (x2 < x1) ? (x2 + (mapX + 1)) : (x2 - (mapX + 1));
	}
	float diffY = _abs(y1 - y2);
	if (diffY > (mapY / 2)) {
		diffY = _abs(_abs(y1 - y2) - (mapY + 1));
		y2 = (y2 < y1) ? (y2 + (mapY + 1)) : (y2 - (mapY + 1));
	}

	if (x2 == x1) {
		if (y2 > y1)
			_(return (3))
		else if (y2 < y1)
			_(return (7))
		else
			_(return (0))
	} else {
		a = (y2 - y1) / (x2 - x1);
		if (x2 > x1) {
			if (a == 0)
				_(return (5))
			else if (a > 0) {
				if (a > 1)
					_(return (3))
				else if (a == 1)
					_(return (4))
				else
					_(return (5))
			} else if (a < 0) {
				if (a < -1)
					_(return (7))
				else if (a == -1)
					_(return (6))
				else
					_(return (5))
			}
		} else {
			if (a == 0)
				_(return (1))
			else if (a > 0) {
				if (a > 1)
					_(return (7))
				else if (a == 1)
					_(return (8))
				else
					_(return (1))
			} else if (a < 0) {
				if (a < -1)
					_(return (3))
				else if (a == -1)
					_(return (2))
				else
					_(return (1))
			}
		}
	}
	return 0;
}

CREATE_FUNCTION_PARAMS(int, getBroadCast, BroadCast broadcast)
{
	int result = 0;
	int correction = CALL_FUNCTION_PARAMS(calcCorrection, broadcast);

	result = CALL_FUNCTION_PARAMS(process_calcul, broadcast);

	if (result == 0)
		return (0);
	result += correction;

	if (result < 0)
		result += 8;
	else if (result > 8)
		result -= 8;
	return result;
}

# endif
