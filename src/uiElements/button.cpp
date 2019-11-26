#include "uiElements/button.h"

#include "general/game.h"

Button::Button(String text, bool isTextCentered, float y)
{
	displayText.setString(text);
	centered = isTextCentered;
	cursorOverButton = false;

	float x;
	if (centered)
	{
		x = SCREEN_WIDTH / 2 - displayText.getGlobalBounds().width / 2;
	}
	else
	{
		x = LEFT_POSITION_X;
	}
	displayText.setPosition(x, y);

	frame->setSize({ displayText.getGlobalBounds().width, displayText.getGlobalBounds().height });
	frame->setFillColor(Color::White);
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
	return displayText.getPosition().y;
}

float Button::getBottomSide()
{
	return getUpperSide() + displayText.getGlobalBounds().height;
}

float Button::getLeftSide()
{
	return displayText.getPosition().x;
}

float Button::getRightSide()
{
	return getLeftSide() + displayText.getGlobalBounds().width;
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
	window->draw(displayText, states);
}