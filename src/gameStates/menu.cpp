#include "menu.h"

#include "general/game.h"

Menu::Menu()
{
	for (int i = 0; i < MENU_BUTTON_AMOUNT; i++)
	{
		buttons[i] = NULL;
	}

	if (Game::interfaceMusic.getStatus()!= Music::Playing) Game::interfaceMusic.play();

	buttons[0] = new Button("Press 'Enter' to play", true, SCREEN_HEIGHT / 2 - MENU_TEXT_SPACING / 2);
	buttons[1] = new Button("Press 'C' to see the credits", true, buttons[0]->getUpperSide() + MENU_TEXT_SPACING);
	buttons[2] = new Button("Press 'Escape' to exit", true, buttons[1]->getUpperSide() + MENU_TEXT_SPACING);
}

Menu::~Menu()
{
	if (Game::currentGameState==gameplay_state)Game::interfaceMusic.stop();
	for (int i = 0; i < MENU_BUTTON_AMOUNT; i++)
	{
		if (buttons[i])
		{
			delete buttons[i];
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
		Game::currentGameState=credits_state;
	}

	if (Keyboard::isKeyPressed(Keyboard::Escape))
	{
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
	for (int i = 0; i < MENU_BUTTON_AMOUNT; i++)
	{
		if (buttons[i])buttons[i]->draw();
	}
}