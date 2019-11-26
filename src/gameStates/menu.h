#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>

#include "uiElements/button.h"

using namespace sf;

const int BUTTON_AMOUNT = 2;
const int TEXT_SPACING = 70;

class Menu
{
	Button* buttons[BUTTON_AMOUNT];
public:
	Menu();
	~Menu();
	void init();
	void checkKeyPressedInput(RenderWindow* &window);
	void update(RenderWindow* &window);
	void draw(RenderWindow* &window);
	void close();
};

#endif