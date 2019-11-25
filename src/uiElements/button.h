#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>

using namespace sf;

class Button
{
	RectangleShape rectangle;
	String displayText;
	bool cursorOverButton;
public:
	Button(float x, float y, String text);
	~Button();
	RectangleShape getRec();
	String getDisplayText();
	bool getCursorOverButton();
	float getUpperSide();
	float getBottomSide();
	float getLeftSide();
	float getRightSide();
	void update();
	void draw();
};

#endif //BUTTON_H