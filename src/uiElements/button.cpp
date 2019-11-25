#include "uiElements/button.h"

Button::Button(float x, float y, String text)
{
	rectangle.setSize({ x, y });
	displayText = text;
	cursorOverButton = false;
}

Button::~Button()
{
}

RectangleShape Button::getRec()
{
	return rectangle;
}

String Button::getDisplayText()
{
	return displayText;
}

bool Button::getCursorOverButton()
{
	if ((Mouse::getPosition().x > getLeftSide() && Mouse::getPosition().x < getRightSide())
		&&
		(Mouse::getPosition().y < getUpperSide() && Mouse::getPosition().x > getBottomSide()))
	{
		return true;
	}
	else
	{
		return false;
	}
}

float Button::getUpperSide()
{
	return rectangle.getPosition().y;
}

float Button::getBottomSide()
{
	return getUpperSide() + rectangle.getSize().y;
}

float Button::getLeftSide()
{
	return rectangle.getPosition().x;
}

float Button::getRightSide()
{
	return getLeftSide() + rectangle.getSize().x;
}

void Button::update()
{
	cursorOverButton = getCursorOverButton();
}

void Button::draw()
{
	if (!cursorOverButton)
	{

	}
	else
	{

	}
}