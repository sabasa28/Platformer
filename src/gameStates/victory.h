#ifndef VICTORY_H
#define VICTORY_H

#include "uiElements/display_text.h"

using namespace sf;

namespace game
{
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
}

#endif //VICTORY_H