#ifndef VICTORY_H
#define VICTORY_H

#include "game_states/screen.h"

using namespace sf;

namespace game
{

class Victory : public Screen
{
const int VICTORY_TEXT_ROWS_AMOUNT = 2;
const float VICTORY_TEXT_SPACING = 50.0f;
public:
	Victory();
	~Victory();
	void checkKeyDownInput();
	void update();
	void draw();
};
}

#endif //VICTORY_H