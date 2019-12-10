#ifndef MENU_H
#define MENU_H

#include "screen.h"

namespace game
{
const int MENU_TEXT_ROWS_AMOUNT = 6;
const int MENU_TITLE_SPACING = 200;
const int MENU_PARAGRAPH_SPACING = 70;
const Vector2f VERSION_TEXT_POS = { 925.0f,5.0f };

class Menu:public Screen
{
	bool muteButtonPressed;

public:
	Menu();
	~Menu();
	void checkKeyDownInput();
	void update();
	void draw();
};
}

#endif //MENU_H