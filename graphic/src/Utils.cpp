/*
** EPITECH PROJECT, 2018
** Utils
** File description:
** Implementation of Utils
*/

#include "Utils.hpp"

std::vector<std::string> Utils::split(const std::string &text, char sep)
{
	std::vector<std::string> tokens;
	std::size_t start = 0;
	std::size_t end = 0;

	while ((end = text.find(sep, start)) != std::string::npos) {
		tokens.push_back(text.substr(start, end - start));
		start = end + 1;
	}
	tokens.push_back(text.substr(start));
	return tokens;
}

unsigned int Utils::stoui(const std::string &str)
{
	return (unsigned int)(stoi(str));
}
