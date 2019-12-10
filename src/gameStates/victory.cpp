#include "victory.h"

#include "general/game.h"

namespace game
{
Victory::Victory()
{
	text.resize(VICTORY_TEXT_ROWS_AMOUNT);

	for (int i = 0; i < VICTORY_TEXT_ROWS_AMOUNT; i++)
	{
		text[i] = NULL;
	}

	text[0] = new DisplayText("YOU WON!", true, SCREEN_HEIGHT / 2 - VICTORY_TEXT_SPACING / 2, Color::White, PARAGRAPH_FONT_SIZE);
	text[1] = new DisplayText("Press 'Enter' to return to menu", true, text[0]->getUpperSide() + VICTORY_TEXT_SPACING, Color::White, PARAGRAPH_FONT_SIZE);
	
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
			Game::buttonSFX.play();
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
	drawText();
}
}