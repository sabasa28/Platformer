#include "gameplay.h"

#include "general/game.h"

Gameplay::Gameplay()
{
	player = NULL;
	platform = NULL;
}

Gameplay::~Gameplay()
{
	if (player) delete player;
	if (platform) delete platform;
}

void Gameplay::init()
{
	player = new Player();
	platform = new Platform(SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2, 300, 150, Color::White);
}

void Gameplay::update(RenderWindow* &window, Event event)
{

	player->checkKeyPressedInput(event);
	player->checkKeyDownInput(event, window);
	player->checkKeyReleasedInput(event);

	player->updateMovement();
	player->updatePosition();
	checkGameplayColls(platform);

}

void Gameplay::draw(RenderWindow* &window)
{
	window->clear();
	window->draw(platform->getRec());
	window->draw(player->getRec());
	window->display();
}

void Gameplay::close()
{

}

float Gameplay::getCollisionMargin(Player* player)
{
	return player->getJumpingSpeed() / 2;
}

void Gameplay::checkGameplayColls(Platform* platform)
{
	switch (platform->checkProximity(player->getRec(), getCollisionMargin(player)))
	{
	case Top:
		if (player->colliding(platform->getRec()))
		{
			player->setJumpState(onGround);
			player->setRecY(platform->getUpperSide() - player->getRec().getSize().y);
		}
		break;
	case Bottom:
		if (player->colliding(platform->getRec()))
		{
			player->setSpeedY(0);
			player->setRecY(platform->getBottomSide());
		}
		break;
	case Right:
		if (player->colliding(platform->getRec()))
		{
			player->setSpeedX(0);
			player->setRecX(platform->getRightSide());
		}
		break;
	case Left:
		if (player->colliding(platform->getRec()))
		{
			player->setSpeedX(0);
			player->setRecX(platform->getLeftSide() - player->getRec().getSize().x);
		}
		break;
	}

	if (player->fallingOffPlatform(platform))
	{
		player->setJumpState(falling);
	}

	player->checkScreenLimits();
}