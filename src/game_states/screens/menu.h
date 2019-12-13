#ifndef MENU_H
#define MENU_H

#include "game_states/screen.h"

namespace game
{
const int MENU_TEXT_ROWS_AMOUNT = 5;
const int MENU_LOGO_SPACING = 225;
const int MENU_PARAGRAPH_SPACING = 70;
const Vector2f VERSION_TEXT_POS = { 925.0f,5.0f };

class Menu : public Screen
{
	const float LOGO_POSITION_Y = 75.0f;

	bool muteButtonPressed;
	Texture logoTexture;
	IntRect* logoTextureRect;
	Sprite logoSprite;

public:
	Menu();
	~Menu();
	void checkKeyDownInput();
	void update();
	void draw();
};
}

#endif //MENU_H