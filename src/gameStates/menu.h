#ifndef MENU_H
#define MENU_H

#include <SFML/Audio.hpp>

#include "uiElements/displayText.h"

using namespace sf;

namespace game
{
const int MENU_TEXT_ROWS_AMOUNT = 5;
const int MENU_TITLE_SPACING = 200;
const int MENU_PARAGRAPH_SPACING = 70;

class Menu
{
	bool muteButtonPressed;
	DisplayText* text[MENU_TEXT_ROWS_AMOUNT];

public:
	Menu();
	~Menu();
	void checkKeyDownInput();
	void update();
	void draw();
};
}

#endif //MENU_H