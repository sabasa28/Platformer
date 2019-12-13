#ifndef DISPLAY_TEXT_H
#define DISPLAY_TEXT_H

#include <SFML/Graphics.hpp>

using namespace sf;

namespace game
{

class DisplayText
{
	const float TEXT_LEFT_POSITION = 50.0f;
	Text text;
	bool centered;
	Vector2f initialPos;

public:
	DisplayText(String text, bool isTextCentered, float y, Color color, int fontSize);
	DisplayText(String text, float x, float y, Color color, int fontSize);
	~DisplayText();
	void setPosition(Vector2f newPos);
	void setPositionY(float y);
	Vector2f getInitialPos();
	bool getCentered();
	Text getText();
	float getUpperSide();
	float getBottomSide();
	float getTextWidth();
	void draw();
};
}

#endif //DISPLAY_TEXT_H
