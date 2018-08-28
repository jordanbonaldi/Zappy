/*
** EPITECH PROJECT, 2018
** Commands
** File description:
** Implementation of Commands
*/

#include "Commands.hpp"

std::map<std::string, CommandFunction> Commands::commands = {
	{"msz", &Commands::msz},
	{"bct", &Commands::bct},
	{"tna", &Commands::tna},
	{"pnw", &Commands::pnw},
	{"ppo", &Commands::ppo},
	{"plv", &Commands::plv},
	{"pin", &Commands::pin},
	{"pex", &Commands::pex},
	{"pbc", &Commands::pbc},
	{"pfk", &Commands::pfk},
	{"pdi", &Commands::pdi},
	{"pic", &Commands::pic},
	{"pie", &Commands::pie},
	{"pdr", &Commands::pdr},
	{"pgt", &Commands::pgt},
	{"enw", &Commands::enw},
	{"eht", &Commands::eht},
	{"ebo", &Commands::ebo},
	{"edi", &Commands::edi},
	{"sgt", &Commands::sgt},
	{"seg", &Commands::seg},
	{"smg", &Commands::smg}
};

void Commands::executeCommand(Data &data, const std::string &command)
{
	auto args = Utils::split(command, ' ');

	auto it = std::find_if(commands.begin(), commands.end(),
		[&](const std::pair<std::string, CommandFunction> &cmd) {
		return cmd.first == args[0];
	});
	if (it != commands.end()) {
		try {
			(*it->second)(data, args);
		} catch (...) {
		}
	}
}

// msz X Y\n
void Commands::msz(Data &data, const std::vector<std::string> &args)
{
	auto &map = data.getMap();
	data.checkArgNumber("msz", (unsigned int)args.size(), 3);
	data.checkInitializedMap("msz");
	map.initialize({stoi(args[1]), stoi(args[2])});
}

// bct X Y q0 q1 q2 q3 q4 q5 q6\n
void Commands::bct(Data &data, const std::vector<std::string> &args)
{
	auto &map = data.getMap();
	data.checkArgNumber("bct", (unsigned int)args.size(), 10);
	data.checkPos("bct", {stoi(args[1]), stoi(args[2])});
	pos_t pos = {stoi(args[1]), stoi(args[2])};
	map[pos.y][pos.x]->setResources(args);
}

// tna N\n * nbr_teams
void Commands::tna(Data &data, const std::vector<std::string> &args)
{
	data.checkArgNumber("tna", (unsigned int)args.size(), 2);
	data.doesTeamNameExists(args[1])
		? throw std::invalid_argument("Team name '"
				 + args[1] + "' is already registered")
		: data.addTeamName(args[1]);
}

// pnw #n X Y O L N\n
void Commands::pnw(Data &data, const std::vector<std::string> &args)
{
	data.checkArgNumber("pnw", (unsigned int)args.size(), 7);
	data.checkTeamName("pnw", args[6]);
	auto &bots = data.getBots();
	pos_t pos = {stoi(args[2]), stoi(args[3])};
	bots.push_back(std::make_unique<Bot>
	        (Utils::stoui(args[1]), pos, Orientation(stoi(args[4])),
	         Utils::stoui(args[5]), args[6]));
}

// ppo n X Y O\n
void Commands::ppo(Data &data, const std::vector<std::string> &args)
{
	data.checkArgNumber("ppo", (unsigned int)args.size(), 5);
	data.checkBotId("ppo", Utils::stoui(args[1]));
	data.checkPos("ppo", {stoi(args[2]), stoi(args[3])});
	data.checkOrientation("ppo", Utils::stoui(args[4]));
	auto &bot = data.getBotById(Utils::stoui(args[1]));
	bot->setPos({stoi(args[2]), stoi(args[3])});
	bot->setOrientation(Orientation(Utils::stoui(args[4])));
}

// plv n L\n
void Commands::plv(Data &data, const std::vector<std::string> &args)
{
	data.checkArgNumber("plv", (unsigned int)args.size(), 3);
	data.checkBotId("plv", Utils::stoui(args[1]));
	data.checkLevel("plv", Utils::stoui(args[2]));
	auto &bot = data.getBotById(Utils::stoui(args[1]));
	bot->setLevel(Utils::stoui(args[2]));
}

// pin n X Y q0 q1 q2 q3 q4 q5 q6\n
void Commands::pin(Data &data, const std::vector<std::string> &args)
{
	data.checkArgNumber("pin", (unsigned int)args.size(), 11);
	data.checkBotId("pin", Utils::stoui(args[1]));
	data.checkPos("pin", {stoi(args[2]), stoi(args[3])});
	auto &bot = data.getBotById(Utils::stoui(args[1]));
	bot->setInventory(args);
	bot->setAnimation(irr::scene::EMAT_CROUCH_STAND);
}

// pex n\n
void Commands::pex(Data &data, const std::vector<std::string> &args)
{
	data.checkArgNumber("pex", (unsigned int)args.size(), 2);
	data.checkBotId("pex", Utils::stoui(args[1]));
	auto &bot = data.getBotById(Utils::stoui(args[1]));
	bot->expulse();
	bot->setAnimation(irr::scene::EMAT_ATTACK);
}

// pbc n M\n
void Commands::pbc(Data &data, const std::vector<std::string> &args)
{
	data.checkArgAtLeastNumber("pbc", (unsigned int)args.size(), 3);
	data.checkBotId("pbc", Utils::stoui(args[1]));
	auto msg = data.extractMessage(args, 2);
	data.checkMessage("pbc", msg);
	auto &bot = data.getBotById(Utils::stoui(args[1]));
	bot->sendMessage(msg);
}

// pfk n\n
void Commands::pfk(Data &data, const std::vector<std::string> &args)
{
	data.checkArgNumber("pfk", (unsigned int)args.size(), 2);
	data.checkBotId("pfk", Utils::stoui(args[1]));
	auto &bot = data.getBotById(Utils::stoui(args[1]));
	bot->setStatus(Bot::Status::LAYING);
}

// pdi n\n
void Commands::pdi(Data &data, const std::vector<std::string> &args)
{
	data.checkArgNumber("pdi", (unsigned int)args.size(), 2);
	data.checkBotId("pdi", Utils::stoui(args[1]));
	auto &bot = data.getBotById(Utils::stoui(args[1]));
	bot->die();
}

// pic X Y L n n ...\n
void Commands::pic(Data &data, const std::vector<std::string> &args)
{
	data.checkArgAtLeastNumber("pic", (unsigned int)args.size(), 5);
	data.checkPos("pic", {stoi(args[1]), stoi(args[2])});
	data.checkLevel("pic", Utils::stoui(args[3]));
	for (unsigned int i = 4 ; i < args.size() ; i++) {
		data.checkBotId("pic", Utils::stoui(args[i]));
		auto &bot = data.getBotById(Utils::stoui(args[i]));
		bot->setStatus(Bot::Status::INCANTING);
		bot->setAnimation(irr::scene::EMAT_SALUTE);
	}
}

// pie X Y R\n
void Commands::pie(Data &data, const std::vector<std::string> &args)
{
	data.checkArgAtLeastNumber("pie", (unsigned int)args.size(), 4);
	data.checkPos("pie", {stoi(args[1]), stoi(args[2])});
	data.checkIncantationResult("pie", Utils::stoui(args[3]));
	pos_t pos = {stoi(args[1]), stoi(args[2])};
	auto &bots = data.getBots();
	for (auto &bot : bots) {
		if (pos.x == bot->getPos().x && pos.y == bot->getPos().y) {
			bot->setStatus(Bot::Status::NORMAL);
			bot->setAnimation(irr::scene::EMAT_STAND);
		}
	}
}

// pdr n i\n
void Commands::pdr(Data &data, const std::vector<std::string> &args) {
	data.checkBotId("pdr", Utils::stoui(args[1]));
	data.checkResourceId("pdr", Utils::stoui(args[2]));
	auto &bot = data.getBotById(Utils::stoui(args[1]));
	bot->dropResource(Resource::Type(Utils::stoui(args[2])));
}

// pgt n i\n
void Commands::pgt(Data &data, const std::vector<std::string> &args) {
	data.checkBotId("pgt", Utils::stoui(args[1]));
	data.checkResourceId("pgt", Utils::stoui(args[2]));
	auto &bot = data.getBotById(Utils::stoui(args[1]));
	bot->collectResource(Resource::Type(Utils::stoui(args[2])));
}

// enw e n X Y\n
void Commands::enw(Data &data, const std::vector<std::string> &args)
{
	data.checkArgNumber("enw", (unsigned int)args.size(), 5);
	data.checkBotId("enw", Utils::stoui(args[2]));
	data.checkPos("enw", {stoi(args[3]), stoi(args[4])});
	auto &eggs = data.getEggs();
	auto &layer = data.getBotById(Utils::stoui(args[2]));
	pos_t pos = {stoi(args[3]), stoi(args[4])};
	eggs.push_back(std::make_unique<Egg> (Utils::stoui(args[1]), pos,
	                                      layer->getTeam()));
	auto &bot = data.getBotById(Utils::stoui(args[2]));
	bot->setStatus(Bot::Status::NORMAL);
}

// eht e\n
void Commands::eht(Data &data, const std::vector<std::string> &args)
{
	data.checkArgNumber("eht", (unsigned int)args.size(), 2);
	data.checkEggId("eht", Utils::stoui(args[1]));
	auto &egg = data.getEggById(Utils::stoui(args[1]));
	egg->setHatching(true);
}

// ebo e\n
void Commands::ebo(Data &data, const std::vector<std::string> &args)
{
	data.checkArgNumber("eht", (unsigned int)args.size(), 2);
	data.checkEggId("eht", Utils::stoui(args[1]));
	auto &egg = data.getEggById(Utils::stoui(args[1]));
	egg->setAlive(false);
}

// edi e\n
void Commands::edi(Data &data, const std::vector<std::string> &args)
{
	data.checkArgNumber("eht", (unsigned int)args.size(), 2);
	data.checkEggId("eht", Utils::stoui(args[1]));
	auto &egg = data.getEggById(Utils::stoui(args[1]));
	egg->setAlive(false);
}

// sgt T\n
void Commands::sgt(Data &data, const std::vector<std::string> &args)
{
	data.checkArgNumber("sgt", (unsigned int)args.size(), 2);
	data.setTimeUnit(std::stof(args[1]));
}

// seg N\n
void Commands::seg(Data &data, const std::vector<std::string> &args)
{
	data.checkArgNumber("sgt", (unsigned int)args.size(), 2);
	data.checkTeamName("sgt", args[1]);
	data.removeTeamName(args[1]);
}

// smg M\n
void Commands::smg(Data &data, const std::vector<std::string> &args)
{
	data.checkArgAtLeastNumber("smg", (unsigned int)args.size(), 3);
	auto msg = data.extractMessage(args, 1);
	data.checkMessage("smg", msg);
	std::cout << ">> server send message: " << msg << std::endl;
}