#include "uiElements/button.h"

#include "general/game.h"

Button::Button(String text, bool isTextCentered, float y)
{
	displayText.setString(text);
	centered = isTextCentered;
	generalFont.loadFromFile("assets/fonts/aescrawl.ttf");
	displayText.setFont(generalFont);

	float x;
	if (centered)
	{
		x = SCREEN_WIDTH / 2 - displayText.getGlobalBounds().width / 2;
	}
	else
	{
		x = LEFT_POSITION;
	}
	displayText.setPosition(x, y);

	frame.setSize({ displayText.getGlobalBounds().width, displayText.getGlobalBounds().height });
	frame.setPosition(displayText.getPosition().x, displayText.getPosition().y);
	frame.setFillColor(Color::White);
}

Button::~Button()
{
}

Text Button::getDisplayText()
{
	return displayText;
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
	
}

void Button::draw()
{
	Game::window->draw(displayText);
}