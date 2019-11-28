#include "menu.h"

#include "general/game.h"

Menu::Menu()
{
	for (int i = 0; i < MENU_BUTTON_AMOUNT; i++)
	{
		buttons[i] = NULL;
	}

	buttons[0] = new Button("Press 'Enter' to play", true, SCREEN_HEIGHT / 2 - MENU_TEXT_SPACING / 2);
	buttons[1] = new Button("Press 'Escape' to exit", true, buttons[0]->getUpperSide() + MENU_TEXT_SPACING);
}

Menu::~Menu()
{
	for (int i = 0; i < MENU_BUTTON_AMOUNT; i++)
	{
		if (buttons[i])
		{
			delete buttons[i];
		}
	}
}

void Menu::checkKeyPressedInput()
{
	if (Keyboard::isKeyPressed(Keyboard::Enter))
	{
		Game::changeGamestate(gameplay_state);
	}
	if (Keyboard::isKeyPressed(Keyboard::Escape))
	{
		Game::window->close();
	}
}

void Menu::update()
{
	checkKeyPressedInput();
}

void Menu::draw()
{
	for (int i = 0; i < MENU_BUTTON_AMOUNT; i++)
	{
		if (buttons[i])buttons[i]->draw();
	}
}