#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>

using namespace sf;

const int BUTTON_LEFT_POSITION = 50;

class Button
{
	Text text;
	bool centered;
	RectangleShape frame;

public:
	Button(String displayText, bool isTextCentered, float y);
	~Button();
	Text getText();
	float getUpperSide();
	float getBottomSide();
	float getLeftSide();
	float getRightSide();
	void draw();
};

#endif //BUTTON_H