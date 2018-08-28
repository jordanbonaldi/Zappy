/*
** EPITECH PROJECT, 2018
** Commands
** File description:
** Declaration of Commands
*/

#ifndef PSU_ZAPPY_2017_COMMANDS_HPP
#define PSU_ZAPPY_2017_COMMANDS_HPP

#include <map>
#include <iostream>
#include <algorithm>

#include "Utils.hpp"
#include "Data.hpp"

typedef void (*CommandFunction)(Data &, const std::vector<std::string> &); // function pointer type

class Commands {
public:
	static std::map<std::string, CommandFunction> commands;
	static void msz(Data &data, const std::vector<std::string> &args);
	static void bct(Data &data, const std::vector<std::string> &args);
	static void tna(Data &data, const std::vector<std::string> &args);
	static void pnw(Data &data, const std::vector<std::string> &args);
	static void ppo(Data &data, const std::vector<std::string> &args);
	static void plv(Data &data, const std::vector<std::string> &args);
	static void pin(Data &data, const std::vector<std::string> &args);
	static void pex(Data &data, const std::vector<std::string> &args);
	static void pbc(Data &data, const std::vector<std::string> &args);
	static void pfk(Data &data, const std::vector<std::string> &args);
	static void pdi(Data &data, const std::vector<std::string> &args);
	static void pic(Data &data, const std::vector<std::string> &args);
	static void pie(Data &data, const std::vector<std::string> &args);
	static void pdr(Data &data, const std::vector<std::string> &args);
	static void pgt(Data &data, const std::vector<std::string> &args);
	static void enw(Data &data, const std::vector<std::string> &args);
	static void eht(Data &data, const std::vector<std::string> &args);
	static void ebo(Data &data, const std::vector<std::string> &args);
	static void edi(Data &data, const std::vector<std::string> &args);
	static void sgt(Data &data, const std::vector<std::string> &args);
	static void seg(Data &data, const std::vector<std::string> &args);
	static void smg(Data &data, const std::vector<std::string> &args);

	static void executeCommand(Data &data, const std::string &command);
};


#endif //PSU_ZAPPY_2017_COMMANDS_HPP
