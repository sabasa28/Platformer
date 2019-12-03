#ifndef CREDITS_H
#define CREDITS_H

#include "uiElements/display_text.h"

using namespace sf;

namespace game
{
const int CREDITS_TEXT_ROWS_AMOUNT = 19;
const int CREDITS_TEXT_SPACING = 50;
const float TEXT_SCROLLING_SPEED = 1.5f;
const float CREDITS_INTIAL_POS = 1700.0f;

class Credits
{
	DisplayText* textRows[CREDITS_TEXT_ROWS_AMOUNT];

public:
	Credits();
	~Credits();
	void checkKeyDownInput();
	void setInitialPos();
	void scroll();
	void update();
	void draw();
};
}

#endif //CREDITS_H