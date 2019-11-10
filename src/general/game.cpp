#include "game.h"

#include <SFML/Graphics.hpp>

#include "gameElements/player.h"
#include "gameElements/level.h"

using namespace sf;

void checkGameplayColls(Player* &player, Platform* &platform);

void executeGame()
{
	Event event;
	Player* player = new Player();
	Platform* platform = new Platform(600, 500, 200, 30, Color::White);
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
		checkGameplayColls(player, platform);
		window.clear();
		window.draw(platform->getRec());
		window.draw(player->getRec());
		window.display();
	}

	if (player != NULL) 
	{
		delete player;
	}
}

void checkGameplayColls(Player* &player, Platform* &platform)
{
	if (player->getJumpstate()==falling && player->bottomSide()>platform->upperSide()&& player->bottomSide() < platform->bottomSide())
	{
		if (player->leftSide()<platform->rightSide()&&player->rightSide()>platform->leftSide())
		{
			player->setJumpstate(onGround);
			player->setRecY(platform->upperSide()-player->getRec().getSize().y);
		}
	}
	if (player->getRec().getPosition().y == platform->upperSide() - player->getRec().getSize().y)
	{
		if (player->leftSide() > platform->rightSide() || player->rightSide() < platform->leftSide())
		{
			player->setJumpstate(falling);
		}
	}
}