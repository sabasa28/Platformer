#include "uiElements/button.h"

#include "general/game.h"

Button::Button(String displayText, bool isTextCentered, float y)
{
	text.setString(displayText);
	text.setFont(Game::generalFont);

	centered = isTextCentered;
	float x;
	if (centered)
	{
		x = SCREEN_WIDTH / 2 - text.getGlobalBounds().width / 2;
	}
	else
	{
		x = BUTTON_LEFT_POSITION;
	}
	text.setPosition(x, y);

	frame.setSize({ text.getGlobalBounds().width, text.getGlobalBounds().height });
	frame.setPosition(text.getPosition().x, text.getPosition().y);
	frame.setFillColor(Color::White);
}

Button::~Button()
{
}

Text Button::getText()
{
	return text;
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

void Button::draw()
{
	Game::window->draw(text);
}