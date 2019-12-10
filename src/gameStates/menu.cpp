#include "menu.h"

#include "general/game.h"

namespace game
{
Menu::Menu()
{
	muteButtonPressed = false;

	text.resize(MENU_TEXT_ROWS_AMOUNT);

	for (int i = 0; i < MENU_TEXT_ROWS_AMOUNT; i++)
	{
		text[i] = NULL;
	}

	text[0] = new DisplayText("CAVE CLIMBER", true, SCREEN_HEIGHT / 6, Color::Yellow, TITLE_FONT_SIZE);
	text[1] = new DisplayText("Press 'Enter' to play ('P' or 'Escape' to pause the game)", true, text[0]->getUpperSide() + MENU_TITLE_SPACING, Color::White, PARAGRAPH_FONT_SIZE);
	text[2] = new DisplayText("Press 'C' to see the credits", true, text[1]->getUpperSide() + MENU_PARAGRAPH_SPACING, Color::White, PARAGRAPH_FONT_SIZE);
	text[3] = new DisplayText("Press 'M' to mute/unmute music", true, text[2]->getUpperSide() + MENU_PARAGRAPH_SPACING, Color::White, PARAGRAPH_FONT_SIZE);
	text[4] = new DisplayText("Press 'Escape' to exit", true, text[3]->getUpperSide() + MENU_PARAGRAPH_SPACING, Color::White, PARAGRAPH_FONT_SIZE);
	text[5] = new DisplayText("v1.0", true, 0.0f, Color::Red, PARAGRAPH_FONT_SIZE);
	
	text[5]->setPosition(VERSION_TEXT_POS);

	if (Game::interfaceMusic.getStatus()!= Music::Playing) Game::interfaceMusic.play();
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

	if (!muteButtonPressed)
	{
		if (Keyboard::isKeyPressed(Keyboard::M))
		{
			Game::buttonSFX.play();
			Game::switchMusicState();
			muteButtonPressed = true;
		}
	}
	else
	{
		if (!Keyboard::isKeyPressed(Keyboard::M))
		{
			muteButtonPressed = false;
		}
	}


	Game::window->setKeyRepeatEnabled(true);
}

void Menu::update()
{
	checkKeyDownInput();
}

void Menu::draw()
{
	drawText();
}
}