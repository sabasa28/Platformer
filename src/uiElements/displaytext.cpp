#include "displaytext.h"

#include "general/game.h"

DisplayText::DisplayText(String displayText, bool isTextCentered, float y, Color color, int fontSize)
{
	text.setString(displayText);
	text.setFont(Game::generalFont);
	text.setFillColor(color);
	text.setCharacterSize(fontSize);
	centered = isTextCentered;

	float x;
	if (centered)
	{
		x = SCREEN_WIDTH / 2 - text.getGlobalBounds().width / 2;
	}
	else
	{
		x = TEXT_LEFT_POSITION;
	}
	text.setPosition(x, y);

	initialPos = text.getPosition();
}

DisplayText::DisplayText(String displayText, float x, float y, Color color, int fontSize)
{
	text.setString(displayText);
	text.setFont(Game::generalFont);
	text.setFillColor(color);
	text.setCharacterSize(fontSize);

	centered = false;
	
	text.setPosition(x, y);

	initialPos = text.getPosition();
}


DisplayText::~DisplayText()
{
}

void DisplayText::setPositionY(float y)
{
	text.setPosition(text.getPosition().x, y);
}

Vector2f DisplayText::getInitialPos()
{
	return initialPos;
}

bool DisplayText::getCentered()
{
	return centered;
}

Text DisplayText::getText()
{
	return text;
}

float DisplayText::getUpperSide()
{
	return text.getPosition().y;
}

float DisplayText::getBottomSide()
{
	return text.getPosition().y + text.getGlobalBounds().height;
}

void DisplayText::draw()
{
	Game::window->draw(text);
}