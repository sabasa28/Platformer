#include "game.h"

#include <SFML/Graphics.hpp>

#include "gameElements/player.h"
#include "gameElements/level.h"

using namespace sf;

void checkGameplayColls(Player* &player, Platform* platform);

void executeGame()
{
	Event event;
	Player* player = new Player();
	Platform* platform = new Platform(SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2 - 150, 300, 300, Color::White);
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
				player->checkKeyPressedInput(event);
				player->checkKeyDownInput(event, window);
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

void checkGameplayColls(Player* &player, Platform* platform)
{
	if (player->onPlatform(platform))
	{
		player->setJumpState(onGround);
		player->setRecY(platform->upperSide() - player->getRec().getSize().y);
	}
	if (player->collidingWithPlatformFromBelow(platform))
	{
		player->setRecY(platform->bottomSide());
	}
	if (player->collidingWithPlatformFromLeft(platform))
	{
		player->setRecX(platform->leftSide() - player->getRec().getSize().x);
	}
	if (player->collidingWithPlatformFromRight(platform))
	{
		player->setRecX(platform->rightSide());
	}
	if (player->fallingOffPlatform(platform))
	{
		player->setJumpState(falling);
	}
}