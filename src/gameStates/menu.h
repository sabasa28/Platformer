#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>

#include "uiElements/button.h"

using namespace sf;

const int BUTTON_AMOUNT = 3;
const int TEXT_SPACING = 20;

class Menu
{
	Button* buttons[BUTTON_AMOUNT];
public:
	Menu();
	~Menu();
	void init();
	void update(/*RenderWindow* &window*/);
	void draw(RenderWindow* &window);
	void close();
};

#endif