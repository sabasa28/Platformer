#include "game.h"
#include "gameElements/player.h"

#include <SFML/Graphics.hpp>

using namespace sf;

void executeGame()
{
	Player* player = new Player();

	RenderWindow window(VideoMode(1000, 600), "Platformer Game");
	window.setFramerateLimit(60);
	while (window.isOpen())
	{
		Event event;
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
				if (event.key.code == Keyboard::Right)
				{
					player->setMoveRight(true);
				}
				if (event.key.code == Keyboard::Left)
				{
					player->setMoveLeft(true);
				}
				if (event.key.code == Keyboard::Up)
				{
					player->setMoveUp(true);
				}
				if (event.key.code == Keyboard::Down)
				{
					player->setMoveDown(true);
				}
			}
			if (event.type == Event::KeyReleased)
			{
				if (event.key.code == Keyboard::Right)
				{
					player->setMoveRight(false);
				}
				if (event.key.code == Keyboard::Left)
				{
					player->setMoveLeft(false);
				}
				if (event.key.code == Keyboard::Up)
				{
					player->setMoveUp(false);
				}
				if (event.key.code == Keyboard::Down)
				{
					player->setMoveDown(false);
				}
			}
			
		}
		player->updateMovement();
		window.clear();
		window.draw(player->getRec());
		window.display();
	}
}