#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>

using namespace sf;

const int LEFT_POSITION = 50;

class Button
{
	Text displayText;
	bool centered;
	RectangleShape frame;

public:
	Button(String text, bool isTextCentered, float y);
	~Button();
	Text getDisplayText();
	float getUpperSide();
	float getBottomSide();
	float getLeftSide();
	float getRightSide();
	void update();
	void draw();
};

#endif //BUTTON_H