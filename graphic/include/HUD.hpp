/*
** EPITECH PROJECT, 2018
** HUD
** File description:
** Declaration of HUD
*/

#ifndef PSU_ZAPPY_2017_HUD_HPP
	#define PSU_ZAPPY_2017_HUD_HPP

#include <irrlicht/irrlicht.h>
#include "Tile.hpp"
#include "Data.hpp"

class HUD
{
public:
	HUD();
	void refresh(Data &data);
	void setSelected(Tile &tile);
	void setUnselected();
private:
	irr::gui::IGUIWindow *parent;
	irr::gui::IGUIComboBox *viewBox;
	irr::gui::IGUICheckBox *shadowBox;
	std::vector<std::pair<irr::gui::IGUIImage *, irr::gui::IGUIStaticText *>>
		resources;
	irr::gui::IGUIStaticText *speed;
	irr::gui::IGUIStaticText *teamsNb;
	irr::gui::IGUIStaticText *playersNb;
	irr::gui::IGUIStaticText *noSelection;
};


#endif //PSU_ZAPPY_2017_HUD_HPP
