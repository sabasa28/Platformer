#ifndef DISPLAY_TEXT_H
#define DISPLAY_TEXT_H

#include <SFML/Graphics.hpp>

using namespace sf;

const int TEXT_LEFT_POSITION = 50;

class DisplayText
{
	Text text;
	bool centered;

public:
	DisplayText(String text, bool isTextCentered, float y);
	~DisplayText();
	Text getText();
	float getUpperSide();
	void draw();
};

#endif //DISPLAY_TEXT_H
