#include "game.h"

#include <SFML/Graphics.hpp>

#include "gameElements/player.h"
#include "gameElements/level.h"

using namespace sf;

void checkGameplayColls(Player* &player, Platform* platform);
float getCollisionMargin(Player* player);

void executeGame()
{
	Event event;
	Player* player = new Player();
	Platform* platform = new Platform(SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2, 300, 150, Color::White);
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
		player->updatePosition();
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

float getCollisionMargin(Player* player)
{
	return player->getJumpingSpeed() / 2;
}

void checkGameplayColls(Player* &player, Platform* platform)
{
	switch (platform->checkProximity(player->getRec(), getCollisionMargin(player)))
	{
	case Top:
		if (player->collidingWithPlatform(platform))
		{
			player->setJumpState(onGround);
			player->setRecY(platform->upperSide() - player->getRec().getSize().y);
		}
		break;
	case Bottom:
		if (player->collidingWithPlatform(platform))
		{
			player->setSpeedY(0);
			player->setRecY(platform->bottomSide());
		}
		break;
	case Right:
		if (player->collidingWithPlatform(platform))
		{
			player->setSpeedX(0);
			player->setRecX(platform->rightSide());
		}
		break;
	case Left:
		if (player->collidingWithPlatform(platform))
		{
			player->setSpeedX(0);
			player->setRecX(platform->leftSide() - player->getRec().getSize().x);
		}
		break;
	}

	if (player->fallingOffPlatform(platform))
	{
		player->setJumpState(falling);
	}

	player->checkScreenLimits();
}