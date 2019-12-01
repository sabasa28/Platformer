#ifndef MENU_H
#define MENU_H

#include <SFML/Audio.hpp>

#include "uiElements/button.h"

using namespace sf;

const int MENU_BUTTON_AMOUNT = 3;
const int MENU_TEXT_SPACING = 70;

class Menu
{
	Button* buttons[MENU_BUTTON_AMOUNT];
	RectangleShape rec;

public:
	Menu();
	~Menu();
	void checkKeyDownInput();
	void update();
	void draw();
};

#endif //MENU_H