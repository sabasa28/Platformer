#include "menu.h"

#include "general/game.h"

Menu::Menu()
{
	for (int i = 0; i < BUTTON_AMOUNT; i++)
	{
		buttons[i] = NULL;
	}

	buttons[0] = new Button("Press 'Enter' to play", true, SCREEN_HEIGHT / 2 - TEXT_SPACING / 2);
	buttons[1] = new Button("Press 'Escape' to exit", true, buttons[0]->getUpperSide() + TEXT_SPACING);
}

Menu::~Menu()
{
	for (int i = 0; i < BUTTON_AMOUNT; i++)
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
	if (buttons[0]) buttons[0]->update();
	if (buttons[1]) buttons[1]->update();

	checkKeyPressedInput();
}

void Menu::draw()
{
	Game::window->clear();

	if (buttons[0])buttons[0]->draw();
	if (buttons[1])buttons[1]->draw();

	Game::window->display();
}