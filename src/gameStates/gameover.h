#ifndef GAME_OVER_H
#define GAME_OVER_H

#include "uiElements/displaytext.h"

using namespace sf;

namespace game
{
const int GAME_OVER_TEXT_ROWS_AMOUNT = 2;
const int GAME_OVER_TEXT_SPACING = 50;

class GameOver
{
	DisplayText* textRows[GAME_OVER_TEXT_ROWS_AMOUNT];

public:
	GameOver();
	~GameOver();
	void checkKeyDownInput();
	void update();
	void draw();
};
}

#endif //GAME_OVER_H