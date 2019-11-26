#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>

using namespace sf;

const int LEFT_POSITION_X = 50;

class Button
{
	Text displayText;
	Font generalFont;
	bool centered;
	bool cursorOverButton;
	RectangleShape frame;
public:
	Button(String text, Vector2f size, bool isTextCentered, float y);
	~Button();
	Text getDisplayText();
	bool getCursorOverButton();
	float getUpperSide();
	float getBottomSide();
	float getLeftSide();
	float getRightSide();
	void update();
	void draw(RenderWindow*& window, RenderStates states);
};

#endif //BUTTON_H