#ifndef VICTORY_H
#define VICTORY_H

#include <SFML/Graphics.hpp>

#include "uiElements/displaytext.h"

using namespace sf;

const int VICTORY_TEXT_ROWS_AMOUNT = 2;
const int VICTORY_TEXT_SPACING = 50;

class Victory
{
	DisplayText* textRows[VICTORY_TEXT_ROWS_AMOUNT];

public:
	Victory();
	~Victory();
	void checkKeyDownInput();
	void update();
	void draw();
};

#endif //VICTORY_H