/*
** EPITECH PROJECT, 2018
** Utils
** File description:
** Declaration of Utils
*/

#ifndef PSU_ZAPPY_2017_UTILS_HPP
#define PSU_ZAPPY_2017_UTILS_HPP

#include <iostream>
#include <vector>

class Utils {
public:
	static std::vector<std::string> split(const std::string &text, char sep);
	static unsigned int stoui(const std::string &str);
};


#endif //PSU_ZAPPY_2017_UTILS_HPP
