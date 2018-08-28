/*
** EPITECH PROJECT, 2018
** Utils
** File description:
** Declaration of Utils
*/

#ifndef ZAPPY_AI_UTILS_HPP
	#define ZAPPY_AI_UTILS_HPP

#include <string>
#include <vector>

class Utils
{
public:
	Utils() = delete;
	static std::vector<std::string> split(const std::string &text, char sep);
};

#endif //ZAPPY_AI_UTILS_HPP
