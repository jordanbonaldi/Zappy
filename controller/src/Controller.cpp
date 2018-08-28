/*
** EPITECH PROJECT, 2018
** Controller
** File description:
** Controller
*/

#include "Controller.hpp"
#include "Controller.moc"

Controller::Controller(const std::string &teamName, const std::string &machineName,
		       bool debugVar, bool isGraphic) : QWidget()
{
	_player = new Player(teamName, machineName, debugVar, isGraphic);
	setWindowTitle(tr("Zappy"));
	QPushButton *pushButton = new QPushButton(this);
	pushButton->setGeometry(458, 20, 160, 160);
	pushButton->setIcon(QIcon("res/Icons/pushx2.png"));
	pushButton->setIconSize(QSize(64, 64));
	connect(pushButton, SIGNAL(clicked()), this, SLOT(eject()));
	QPushButton *takeObjButton = new QPushButton(this);
	takeObjButton->setGeometry(458, 440, 160, 120);
	takeObjButton->setIcon(QIcon("res/Icons/getx2.png"));
	takeObjButton->setIconSize(QSize(64, 64));
	connect(takeObjButton, SIGNAL(clicked()), this, SLOT(getObject()));
	QPushButton *setObjButton = new QPushButton(this);
	setObjButton->setGeometry(658, 440, 160, 120);
	setObjButton->setIcon(QIcon("res/Icons/dropx2.png"));
	setObjButton->setIconSize(QSize(64, 64));
	connect(setObjButton, SIGNAL(clicked()), this, SLOT(dropObject()));
	QPushButton *incantButton = new QPushButton("Incantation", this);
	incantButton->setGeometry(458, 220, 360, 140);
	connect(incantButton, SIGNAL(clicked()), this, SLOT(startIncantation()));
	drawInventoryBackground();
	_connected = new QLabel(this);
	_connected->setGeometry(658, 110, 160, 50);
	refreshNbPlayer();
	QFont *font = new QFont();
	font->setPointSize(20);
	_level = new QLabel(this);
	_level->setGeometry(658, 40, 160, 50);
	_level->setFont(*font);
	refreshLevel();
	QPushButton *lookButton = new QPushButton(this);
	lookButton->setGeometry(26, 20, 400, 30);
	lookButton->setIcon(QIcon("res/Icons/eye.png"));
	lookButton->setIconSize(QSize(32, 32));
	connect(lookButton, SIGNAL(clicked()), this, SLOT(look()));
	QPushButton *leftButton = new QPushButton(this);
	leftButton->setGeometry(127, 497, 63, 63);
	leftButton->setIcon(QIcon("res/Icons/leftx2.png"));
	leftButton->setIconSize(QSize(64, 64));
	connect(leftButton, SIGNAL(clicked()), this, SLOT(turnLeft()));
	QPushButton *upButton = new QPushButton(this);
	upButton->setGeometry(190, 433, 63, 127);
	upButton->setIcon(QIcon("res/Icons/upx2.png"));
	upButton->setIconSize(QSize(64, 64));
	connect(upButton, SIGNAL(clicked()), this, SLOT(move()));
	QPushButton *rightButton = new QPushButton(this);
	rightButton->setGeometry(253, 497, 63, 63);
	rightButton->setIcon(QIcon("res/Icons/rightx2.png"));
	rightButton->setIconSize(QSize(64, 64));
	connect(rightButton, SIGNAL(clicked()), this, SLOT(turnRight()));
	_lookItem = new QTableWidget(0, 3, this);
	_lookItem->setSelectionBehavior(QAbstractItemView::SelectRows);
	QStringList columnName;
	columnName << tr("Name") << tr("Quantity") << tr("Pos.");
	_lookItem->setHorizontalHeaderLabels(columnName);
	_lookItem->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
	_lookItem->verticalHeader()->hide();
	_lookItem->setGeometry(26, 50, 400, 350);
	_inventory = _player->getInventory();
	_inventoryLabels["food"] = new QLabel(this);
	_inventoryLabels["food"]->setText(std::to_string(_inventory.food).c_str());
	_inventoryLabels["linemate"] = new QLabel(this);
	_inventoryLabels["linemate"]->setText(std::to_string(_inventory.linemate).c_str());
	_inventoryLabels["deraumere"] = new QLabel(this);
	_inventoryLabels["deraumere"]->setText(std::to_string(_inventory.deraumere).c_str());
	_inventoryLabels["sibur"] = new QLabel(this);
	_inventoryLabels["sibur"]->setText(std::to_string(_inventory.sibur).c_str());
	_inventoryLabels["mendiane"] = new QLabel(this);
	_inventoryLabels["mendiane"]->setText(std::to_string(_inventory.mendiane).c_str());
	_inventoryLabels["phiras"] = new QLabel(this);
	_inventoryLabels["phiras"]->setText(std::to_string(_inventory.phiras).c_str());
	_inventoryLabels["thystame"] = new QLabel(this);
	_inventoryLabels["thystame"]->setText(std::to_string(_inventory.thystame).c_str());
	for (auto label : _inventoryLabels) {
		label.second->setGeometry(44 + (116 * Inventory::getResourceFromString(label.first)), 618, 64, 64);
		label.second->setAlignment(Qt::AlignRight | Qt::AlignBottom);
	}
	QStringList items = {"food", "linemate", "deraumere", "sibur", "mendiane", "phiras", "thystame"};
	_takeObjCB = new QComboBox(this);
	_takeObjCB->addItems(items);
	_takeObjCB->setGeometry(458, 400, 160, 30);
	_setObjCB = new QComboBox(this);
	_setObjCB->addItems(items);
	_setObjCB->setGeometry(658, 400, 160, 30);
	QTimer *timer = new QTimer(this);
	timer->start(500);
	connect(timer, SIGNAL(timeout()), this, SLOT(refreshActions()));
}

void Controller::connection(CommunicationHelper *communicationHelper)
{
	_player->connect(communicationHelper);
}

void Controller::move()
{
	_player->move();
}

void Controller::turnRight()
{
	_player->turnRight();
}

void Controller::turnLeft()
{
	_player->turnLeft();
}

bool Controller::eject()
{
	return _player->eject();
}

void Controller::startIncantation()
{
	_player->startIncantation();
}

void Controller::look()
{
	int zone = 0;
	int row;
	std::map<Inventory::Resource, int> items;

	_player->look();
	_frontTiles = _player->getFrontTiles();
	_lookItem->setRowCount(0);
	for (auto tile : _frontTiles) {
		items = stackItems(tile);
		for (auto item : items) {
			if (item.second > 0) {
				QTableWidgetItem *objectType = new QTableWidgetItem(Inventory::getStringFromResource(item.first).c_str());
				objectType->setIcon(QIcon(QPixmap(chooseIcon(item.first, "").c_str())));
				QTableWidgetItem *objectNbr = new QTableWidgetItem(std::to_string(item.second).c_str());
				objectNbr->setTextAlignment(Qt::AlignCenter);
				QTableWidgetItem *objectPos = new QTableWidgetItem(std::to_string(zone).c_str());
				objectPos->setTextAlignment(Qt::AlignCenter);
				row = _lookItem->rowCount();
				_lookItem->insertRow(row);
				_lookItem->setItem(row, 0, objectType);
				_lookItem->setItem(row, 1, objectNbr);
				_lookItem->setItem(row, 2, objectPos);
			}
		}
		zone++;
	}
}

void Controller::getObject()
{
	std::string item = _takeObjCB->itemText(_takeObjCB->currentIndex()).toUtf8().constData();
	_player->getObject(Inventory::getResourceFromString(item.c_str()));
	updateInventoryCount();
}

void Controller::dropObject()
{
	std::string item = _setObjCB->itemText(_setObjCB->currentIndex()).toUtf8().constData();
	_player->dropObject(Inventory::getResourceFromString(item.c_str()));
	updateInventoryCount();
}

void Controller::refreshNbPlayer()
{
	_connected->setText(std::string("Number of players: " +
					std::to_string(_player->countPlayersInCurrentTile())).c_str());
}

void Controller::setArgv(char *first, char **av)
{
	_player->setArgv(first, av);
}

std::string Controller::chooseIcon(Inventory::Resource resource,
				   std::string scale)
{
	switch (resource) {
		case Inventory::FOOD:
			return "res/Icons/food" + scale + ".png";
		case Inventory::LINEMATE:
			return "res/Icons/yellow" + scale + ".png";
		case Inventory::DERAUMERE:
			return "res/Icons/green" + scale + ".png";
		case Inventory::SIBUR:
			return "res/Icons/red" + scale + ".png";
		case Inventory::MENDIANE:
			return "res/Icons/white" + scale + ".png";
		case Inventory::PHIRAS:
			return "res/Icons/blue" + scale + ".png";
		case Inventory::THYSTAME:
			return "res/Icons/purple" + scale + ".png";
		case Inventory::PLAYER:
			return "res/Icons/player" + scale + ".png";
		default:
			return "res/Icons/blue.png";
	}
}

void Controller::updateInventoryCount()
{
	_inventory = _player->getInventory();
	_inventoryLabels["food"]->setText(std::to_string(_inventory.food).c_str());
	_inventoryLabels["linemate"]->setText(std::to_string(_inventory.linemate).c_str());
	_inventoryLabels["deraumere"]->setText(std::to_string(_inventory.deraumere).c_str());
	_inventoryLabels["sibur"]->setText(std::to_string(_inventory.sibur).c_str());
	_inventoryLabels["mendiane"]->setText(std::to_string(_inventory.mendiane).c_str());
	_inventoryLabels["phiras"]->setText(std::to_string(_inventory.phiras).c_str());
	_inventoryLabels["thystame"]->setText(std::to_string(_inventory.thystame).c_str());
}

std::map<Inventory::Resource, int>
Controller::stackItems(std::vector<Inventory::Resource> items)
{
	std::map<Inventory::Resource, int> stacked;
	stacked[Inventory::FOOD] = 0;
	stacked[Inventory::LINEMATE] = 0;
	stacked[Inventory::DERAUMERE] = 0;
	stacked[Inventory::SIBUR] = 0;
	stacked[Inventory::MENDIANE] = 0;
	stacked[Inventory::PHIRAS] = 0;
	stacked[Inventory::THYSTAME] = 0;
	stacked[Inventory::PLAYER] = 0;

	for (auto item : items)
		stacked[item] += 1;
	return stacked;
}

void Controller::refreshActions()
{
	_player->refreshActions();
	refreshNbPlayer();
	refreshLevel();
	updateInventoryCount();
}

bool Controller::canGet(Inventory::Resource resource, int amount)
{
	_player->look();
	_frontTiles = _player->getFrontTiles();
	std::map<Inventory::Resource, int> dispo = stackItems(_frontTiles[0]);

	return amount <= dispo[resource];
}

void Controller::refreshLevel()
{
	_level->setText(std::string("Level: " +
					std::to_string(_player->getLevel())).c_str());
}

void Controller::drawInventoryBackground()
{
	for (int i = 0; i < 7; i++) {
		_invBackground.push_back(new QLabel(this));
		_invBackground.back()->setStyleSheet("border-style: solid; border-width: 1px;");
		_invBackground.back()->setGeometry(26 + (116 * i), 600, 100, 100);
		_invBackground.back()->setPixmap(QPixmap(
			chooseIcon(Inventory::Resource(i), "x2").c_str()));
		_invBackground.back()->setAlignment(Qt::AlignCenter);
	}
}
