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
}

void Menu::init()
{
	buttons[0] = new Button("Play", true, SCREEN_HEIGHT / 2);
	buttons[1] = new Button("How to play", true, buttons[0]->getUpperSide() + TEXT_SPACING);
	buttons[2] = new Button("Exit", true, buttons[1]->getUpperSide() + TEXT_SPACING);
}

void Menu::update(/*RenderWindow* &window*/)
{

}

void Menu::draw(RenderWindow* &window)
{
	window->clear();

	if (buttons[0])buttons[0]->draw(window, RenderStates::Default);
	if (buttons[1])buttons[1]->draw(window, RenderStates::Default);
	if (buttons[2])buttons[2]->draw(window, RenderStates::Default);

	window->display();
}

void Menu::close()
{

}