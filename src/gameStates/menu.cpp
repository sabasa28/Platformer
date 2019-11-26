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
	buttons[0] = new Button("Play", {250, 50}, true, SCREEN_HEIGHT / 2);
	buttons[1] = new Button("How to play", { 250, 50 }, true, buttons[0]->getUpperSide() + TEXT_SPACING);
	buttons[2] = new Button("Exit", { 250, 50 }, true, buttons[1]->getUpperSide() + TEXT_SPACING);
}

void Menu::update()
{
	if (buttons[0])buttons[0]->update();
	if (buttons[1])buttons[1]->update();
	if (buttons[2])buttons[2]->update();

	if (buttons[0]->getCursorOverButton())
	{
		cout << "asdfasdfas";
	}
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