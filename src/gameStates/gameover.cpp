#include "gameover.h"

#include "general/game.h"

GameOver::GameOver()
{
	for (int i = 0; i < GAME_OVER_TEXT_ROWS_AMOUNT; i++)
	{
		textRows[i] = NULL;
	}

	textRows[0] = new DisplayText("GAME OVER", true, SCREEN_HEIGHT / 2 - MENU_TEXT_SPACING / 2);
	textRows[1] = new DisplayText("Press 'Enter' to return to menu", true, textRows[0]->getUpperSide() + GAME_OVER_TEXT_SPACING);

	Game::interfaceMusic.play();
}

GameOver::~GameOver()
{
	for (int i = 0; i < GAME_OVER_TEXT_ROWS_AMOUNT; i++)
	{
		if (textRows[i]) delete textRows[i];
	}

	if(Game::currentGameState!=menu_state) Game::interfaceMusic.stop();
}

void GameOver::checkKeyDownInput()
{
	Game::window->setKeyRepeatEnabled(false);

	if (Keyboard::isKeyPressed(Keyboard::Enter))
	{
		if (!Game::getGameStateInputActive())
		{
			Game::setGameStateInputActive(true);
			Game::currentGameState = menu_state;
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

void GameOver::update()
{
	checkKeyDownInput();
}

void GameOver::draw()
{
	for (int i = 0; i < GAME_OVER_TEXT_ROWS_AMOUNT; i++)
	{
		if (textRows[i]) textRows[i]->draw();
	}
}