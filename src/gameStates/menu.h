#ifndef MENU_H
#define MENU_H

#include "uiElements/display_text.h"

using namespace sf;

namespace game
{
const int MENU_TEXT_ROWS_AMOUNT = 6;
const int MENU_TITLE_SPACING = 200;
const int MENU_PARAGRAPH_SPACING = 70;
const Vector2f VERSION_TEXT_POS = { 925.0f,5.0f };

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