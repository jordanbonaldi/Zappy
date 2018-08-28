/*
** EPITECH PROJECT, 2018
** Controller
** File description:
** Declaration of Controller
*/

#ifndef CONTROLLER_HPP
	#define CONTROLLER_HPP

#include <QMainWindow>
#include <QWidget>
#include <QApplication>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QObject>
#include <QCoreApplication>
#include <QDialog>
#include <QtCore>
#include <QShortcut>
#include <QComboBox>
#include <QTableWidget>
#include <QHeaderView>
#include <iostream>
#include <vector>
#include <sys/types.h>
#include <cstdlib>
#include <string>
#include <sstream>
#include <map>
#include "Player.hpp"
#include "Utils.hpp"

class Controller : public QWidget {
	Q_OBJECT
public:
	Controller(const std::string &teamName, const std::string &machineName,
		   bool debugVar, bool isGraphic = true);
	void connection(CommunicationHelper *communicationHelper);
	void setArgv(char *, char **);
	std::string chooseIcon(Inventory::Resource resource, std::string scale);
	void updateInventoryCount();
	std::map<Inventory::Resource, int> stackItems(std::vector<Inventory::Resource>);
	void refreshNbPlayer();
	void refreshLevel();
	bool canGet(Inventory::Resource resource, int amount);
	void drawInventoryBackground();

public slots:
	void move();
	void turnRight();
	void turnLeft();
	bool eject();
	void startIncantation();
	void look();
	void getObject();
	void dropObject();
	void refreshActions();

private:
	Player *_player;
	std::vector<std::vector<Inventory::Resource>> _frontTiles;
	Inventory _inventory;

	QTableWidget *_lookItem;
	QComboBox *_takeObjCB;
	QComboBox *_setObjCB;
	QLabel *_connected;
	QLabel *_level;
	std::vector<QLabel *> _invBackground;
	std::map<std::string, QLabel *> _inventoryLabels;
};

#endif //CONTROLLER_HPP
