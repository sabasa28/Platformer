#include "game_over.h"

#include "general/game.h"

namespace game
{
GameOver::GameOver()
{
	text.resize(GAME_OVER_TEXT_ROWS_AMOUNT);

	for (int i = 0; i < GAME_OVER_TEXT_ROWS_AMOUNT; i++)
	{
		text[i] = NULL;
	}

	text[0] = new DisplayText("GAME OVER", true, SCREEN_HEIGHT / 2 - GAME_OVER_TEXT_SPACING / 2, Color::White, PARAGRAPH_FONT_SIZE);
	text[1] = new DisplayText("Press 'Enter' to return to menu", true, text[0]->getUpperSide() + GAME_OVER_TEXT_SPACING, Color::White, PARAGRAPH_FONT_SIZE);

	Game::interfaceMusic.play();
}

GameOver::~GameOver()
{
	for (int i = 0; i < GAME_OVER_TEXT_ROWS_AMOUNT; i++)
	{
		if (text[i]) delete text[i];
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
			if (!Game::getAudioMuted())
			{
				Game::buttonSFX.play();
			}
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
	drawText();
}

}