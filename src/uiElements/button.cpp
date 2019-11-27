#include "uiElements/button.h"

#include "general/game.h"

Button::Button(String text, Vector2f size, bool isTextCentered, float y)
{
	displayText.setString(text);
	centered = isTextCentered;
	cursorOverButton = false;

	float x;
	if (centered)
	{
		x = SCREEN_WIDTH / 2.5;
	}
	else
	{
		x = LEFT_POSITION_X;
	}
	displayText.setPosition(x, y);

	generalFont.loadFromFile("assets/fonts/aescrawl.ttf");
	displayText.setFont(generalFont);
	frame.setSize(size);
	frame.setFillColor(Color::Blue);
	frame.setPosition(displayText.getPosition().x-25.0f, displayText.getPosition().y);
}

Button::~Button()
{
}

Text Button::getDisplayText()
{
	return displayText;
}

bool Button::getCursorOverButton()
{
	if ((Mouse::getPosition().x > getLeftSide() && Mouse::getPosition().x < getRightSide())
		&&
		(Mouse::getPosition().y > getUpperSide() && Mouse::getPosition().x < getBottomSide()))
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
	return frame.getPosition().y;
}

float Button::getBottomSide()
{
	return getUpperSide() + frame.getSize().y;
}

float Button::getLeftSide()
{
	return frame.getPosition().x;
}

float Button::getRightSide()
{
	return getLeftSide() + frame.getSize().x;
}

void Button::update()
{
	cursorOverButton = getCursorOverButton();

	if (getCursorOverButton())
	{
		if (displayText.getFillColor() != Color::White)
		{
			displayText.setFillColor(Color::White);
		}
	}
	else
	{
		if (displayText.getFillColor() != Color::White)
		{
			displayText.setFillColor(Color::White);
		}
	}
}

void Button::draw(RenderWindow*& window, RenderStates states)
{
	window->draw(frame);
	window->draw(displayText, states);
}