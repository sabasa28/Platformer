#include "menu.h"

#include "general/game.h"

Menu::Menu()
{
	for (int i = 0; i < MENU_TEXT_ROWS_AMOUNT; i++)
	{
		text[i] = NULL;
	}

	if (Game::interfaceMusic.getStatus()!= Music::Playing) Game::interfaceMusic.play();

	text[0] = new DisplayText("CAVE CLIMBER", true, SCREEN_HEIGHT / 6, Color::Yellow, TITLE_FONT_SIZE);
	text[1] = new DisplayText("Press 'Enter' to play ('P' or 'Escape' to pause the game)", true, text[0]->getUpperSide() + MENU_TITLE_SPACING, Color::White, PARAGRAPH_FONT_SIZE);
	text[2] = new DisplayText("Press 'C' to see the credits", true, text[1]->getUpperSide() + MENU_PARAGRAPH_SPACING, Color::White, PARAGRAPH_FONT_SIZE);
	text[3] = new DisplayText("Press 'Escape' to exit", true, text[2]->getUpperSide() + MENU_PARAGRAPH_SPACING, Color::White, PARAGRAPH_FONT_SIZE);
}

Menu::~Menu()
{
	if (Game::currentGameState==gameplay_state) Game::interfaceMusic.stop();
	for (int i = 0; i < MENU_TEXT_ROWS_AMOUNT; i++)
	{
		if (text[i])
		{
			delete text[i];
		}
	}
}

void Menu::checkKeyDownInput()
{
	Game::window->setKeyRepeatEnabled(false);

	if (Keyboard::isKeyPressed(Keyboard::Enter))
	{
		if (!Game::getGameStateInputActive())
		{
			Game::buttonSFX.play();
			Game::setGameStateInputActive(true);
			Game::currentGameState=gameplay_state;
		}
	}
	else
	{
		if (Game::getGameStateInputActive())
		{
			Game::setGameStateInputActive(false);
		}
	}

	if (Keyboard::isKeyPressed(Keyboard::C))
	{
		Game::buttonSFX.play();
		Game::currentGameState=credits_state;
	}

	if (Keyboard::isKeyPressed(Keyboard::Escape))
	{
		Game::buttonSFX.play();
		Game::window->close();
	}

	Game::window->setKeyRepeatEnabled(true);
}

void Menu::update()
{
	checkKeyDownInput();
}

void Menu::draw()
{
	for (int i = 0; i < MENU_TEXT_ROWS_AMOUNT; i++)
	{
		if (text[i]) text[i]->draw();
	}
}