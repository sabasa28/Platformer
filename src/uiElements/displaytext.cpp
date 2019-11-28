#include "displaytext.h"

#include "general/game.h"

DisplayText::DisplayText(String displayText, bool isTextCentered, float y)
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
		x = TEXT_LEFT_POSITION;
	}
	text.setPosition(x, y);
}

DisplayText::~DisplayText()
{
}

Text DisplayText::getText()
{
	return text;
}

float DisplayText::getUpperSide()
{
	return text.getPosition().y;
}

void DisplayText::draw()
{
	Game::window->draw(text);
}