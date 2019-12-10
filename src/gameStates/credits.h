#ifndef CREDITS_H
#define CREDITS_H

#include "screen.h"

using namespace sf;
using namespace std;

namespace game
{
const int CREDITS_TEXT_ROWS_AMOUNT = 19;
const int CREDITS_TEXT_SPACING = 50;
const float TEXT_SCROLLING_SPEED = 1.5f;
const float CREDITS_INTIAL_POS = 1700.0f;

class Credits:public Screen
{

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