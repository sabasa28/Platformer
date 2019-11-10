#include "game.h"
#include "gameElements/player.h"

#include <SFML/Graphics.hpp>

using namespace sf;

void executeGame()
{
	Event event;
	Player* player = new Player();

	RenderWindow window(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Platformer Game");
	window.setFramerateLimit(60);
	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			if (event.type == Event::KeyPressed)
			{
				if (event.key.code == Keyboard::Escape)
				{
					window.close();
				}
				player->checkKeyPressedInput(event);

				window.setKeyRepeatEnabled(false);
				if (event.key.code == Keyboard::Space)
				{
					player->setJump(true);
				}
				window.setKeyRepeatEnabled(true);
			}
			if (event.type == Event::KeyReleased)
			{
				player->checkKeyReleasedInput(event);
			}
		}

		player->updateMovement();
		window.clear();
		window.draw(player->getRec());
		window.display();
	}

	if (player != NULL) 
	{
		delete player;
	}
}