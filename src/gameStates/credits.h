#ifndef CREDITS_H
#define CREDITS_H

#include <SFML/Graphics.hpp>

#include "uiElements/displaytext.h"

using namespace sf;

const int CREDITS_TEXT_ROWS_AMOUNT = 12;
const int CREDITS_TEXT_SPACING = 50;
const float TEXT_SCROLLING_SPEED = 1.5f;
const float CREDITS_INTIAL_POS = 1250.0f;

class Credits
{
	DisplayText* textRows[CREDITS_TEXT_ROWS_AMOUNT];

public:
	Credits();
	~Credits();
	void setInitialPos();
	void scroll();
	void checkKeyDownInput();
	void update();
	void draw();
};

#endif //CREDITS_H