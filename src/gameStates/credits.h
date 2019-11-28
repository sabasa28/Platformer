#ifndef CREDITS_H
#define CREDITS_H

#include <SFML/Graphics.hpp>

#include "uiElements/displaytext.h"

using namespace sf;

const int CREDITS_TEXT_ROWS_AMOUNT = 2;
const int CREDITS_TEXT_SPACING = 50;

class Credits
{
	DisplayText* textRows[CREDITS_TEXT_ROWS_AMOUNT];

public:
	Credits();
	~Credits();
	void checkKeyDownInput();
	void update();
	void draw();
};

#endif //CREDITS_H