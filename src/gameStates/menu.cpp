#include "menu.h"

#include "general/game.h"

Menu::Menu()
{
	for (int i = 0; i < BUTTON_AMOUNT; i++)
	{
		buttons[i] = NULL;
	}
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

void Menu::init()
{
	buttons[0] = new Button("Enter to play", {250, 50}, true, SCREEN_HEIGHT / 2);
	buttons[1] = new Button("Escape to exit", { 250, 50 }, true, buttons[0]->getUpperSide() + TEXT_SPACING);
}

void Menu::checkKeyPressedInput(RenderWindow* &window)
{
	if (Keyboard::isKeyPressed(Keyboard::Enter))
	{
		Game::changeGamestate(gameplay_state);
	}
	if (Keyboard::isKeyPressed(Keyboard::Escape))
	{
		window->close();
	}
}

void Menu::update(RenderWindow* &window)
{
	if (buttons[0])buttons[0]->update();
	if (buttons[1])buttons[1]->update();

	checkKeyPressedInput(window);
}

void Menu::draw(RenderWindow* &window)
{
	window->clear();

	if (buttons[0])buttons[0]->draw(window, RenderStates::Default);
	if (buttons[1])buttons[1]->draw(window, RenderStates::Default);

	window->display();
}

void Menu::close()
{

}