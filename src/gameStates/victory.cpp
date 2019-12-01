#include "victory.h"

#include "general/game.h"

Victory::Victory()
{
	for (int i = 0; i < VICTORY_TEXT_ROWS_AMOUNT; i++)
	{
		textRows[i] = NULL;
	}

	textRows[0] = new DisplayText("YOU WON!", true, SCREEN_HEIGHT / 2 - VICTORY_TEXT_SPACING / 2);
	textRows[1] = new DisplayText("Press 'Enter' to return to menu", true, textRows[0]->getUpperSide() + VICTORY_TEXT_SPACING);
	
	Game::interfaceMusic.play();
}

Victory::~Victory()
{
	if(Game::currentGameState!=menu_state)Game::interfaceMusic.stop();
}

void Victory::checkKeyDownInput()
{
	Game::window->setKeyRepeatEnabled(false);

	if (Keyboard::isKeyPressed(Keyboard::Enter))
	{
		if (!Game::getGameStateInputActive())
		{
			Game::setGameStateInputActive(true);
			Game::currentGameState=menu_state;
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

void Victory::update()
{
	checkKeyDownInput();
}

void Victory::draw()
{
	for (int i = 0; i < GAME_OVER_TEXT_ROWS_AMOUNT; i++)
	{
		if (textRows[i]) textRows[i]->draw();
	}
}