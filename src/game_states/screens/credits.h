#ifndef CREDITS_H
#define CREDITS_H

#include "game_states/screen.h"

using namespace sf;
using namespace std;

namespace game
{

class Credits : public Screen
{
const int CREDITS_TEXT_ROWS_AMOUNT = 19;
const float CREDITS_TEXT_SPACING = 50.0f;
const float TEXT_SCROLLING_SPEED = 1.5f;//90.0f;
const float CREDITS_INTIAL_POS = 1700.0f;

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