#include "credits.h"

#include "general/game.h"

Credits::Credits()
{
	for (int i = 0; i < CREDITS_TEXT_ROWS_AMOUNT; i++)
	{
		textRows[i] = NULL;
	}

	textRows[0] = new DisplayText("aca van a estar los creditos xd", true, SCREEN_HEIGHT / 2 - CREDITS_TEXT_SPACING / 2);
	textRows[1] = new DisplayText("Press 'Enter' to return to menu", true, textRows[0]->getUpperSide() + CREDITS_TEXT_SPACING);
}

Credits::~Credits()
{
}

void Credits::checkKeyDownInput()
{
	Game::window->setKeyRepeatEnabled(false);

	if (Keyboard::isKeyPressed(Keyboard::Enter))
	{
		if (!Game::getGameStateInputActive())
		{
			Game::setGameStateInputActive(true);
			Game::changeGamestate(menu_state);
		}
	}
	else
	{
		if (Game::getGameStateInputActive())
		{
			Game::setGameStateInputActive(false);
		}
	}

	Game::window->setKeyRepeatEnabled(true);
}

void Credits::update()
{
	checkKeyDownInput();
}

void Credits::draw()
{
	for (int i = 0; i < GAME_OVER_TEXT_ROWS_AMOUNT; i++)
	{
		if (textRows[i]) textRows[i]->draw();
	}
}