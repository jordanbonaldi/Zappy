#!/usr/bin/python3

from math import exp, sqrt, ceil, pi, factorial, atan, degrees
from sys import exit, argv

def process_calcul(x1, y1, x2, y2, mapX, mapY):
	diffX = abs(x1 - x2)
	if (diffX > (mapX / 2)):
		diffX = abs(abs(x1 - x2) - (mapX + 1))
		x2 = x2 + (mapX + 1) if x2 < x1 else x2 - (mapX + 1)
	diffY = abs(y1 - y2)
	if (diffY > (mapY / 2)):
		diffY = abs(abs(y1 - y2) - (mapY + 1))
		y2 = y2 + (mapY + 1) if y2 < y1 else y2 - (mapY + 1)
#	length = sqrt((diffX ** 2) + (diffY ** 2))
#	print("length = %f" % length)
	print("new x1 = %f" % x1)
	print("new x2 = %f" % x2)
	print("new y1 = %f" % y1)
	print("new y2 = %f" % y2)
#	result = degrees(atan(diffY / diffX))
#	print("result = %f" % result)
	if (x2 == x1):
		if (y2 > y1):
			#print("EN BAS")
			return (3)
		elif (y2 < y1):
			#print("EN HAUT")
			return (7)
		else:
			#print("HERE")
			return (0)
	else:
		a = (y2 - y1) / (x2 - x1)
		print("a = %d" % a)
		if (x2 > x1):
			if (a == 0):
				#print("A DROITE")
				return (5)
			elif (a > 0):
				if (a > 1):
					#print("EN BAS A TRES A DROITE")
					return (3)
				elif (a == 1):
					#print("EN BAS MILIEU A DROITE")
					return (4)
				else:
					#print("EN BAS A DROITE")
					return (5)
			elif (a < 0):
				if (a < -1):
					#print("EN HAUT A TRES A DROITE")
					return (7)
				elif (a == -1):
					#print("EN HAUT MILIEU A DROITE")
					return (6)
				else:
					#print("EN HAUT A DROITE")
					return (5)
		else:
			if (a == 0):
				#print("A GAUCHE")
				return (1)
			elif (a > 0):
				if (a > 1):
					#print("EN HAUT A TRES A GAUCHE")
					return (7)
				elif (a == 1):
					#print("EN HAUT MILIEU A GAUCHE")
					return (8)
				else:
					#print("EN HAUT A GAUCHE")
					return (1)
			elif (a < 0):
				if (a < -1):
					#print("EN BAS A TRES A GAUCHE")
					return (3)
				elif (a == -1):
					#print("EN BAS MILIEU A GAUCHE")
					return (2)
				else:
					#print("EN BAS A GAUCHE")
					return (1)

def main(argv):
	if len(argv) != 8:
		print("error must be 7 args")
		exit(84)
	x1 = int(argv[1])
	y1 = int(argv[2])
	x2 = int(argv[3])
	y2 = int(argv[4])
	mapX = int(argv[5])
	mapY = int(argv[6])
	direction = int(argv[7])

	correction = 0

	if (direction == 0):
		correction = -2
	if (direction == 1):
		correction = -4
	if (direction == 2):
		correction = 2

	result = process_calcul(x1, y1, x2, y2, mapX, mapY)
	result += correction
	if (result < 0):
		result += 8
	#print(result)
	exit(result)

if __name__ == "__main__":
	main(argv)
