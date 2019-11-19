#include "gameplay.h"

#include "general/game.h"

Gameplay::Gameplay()
{
	player = NULL;
	platform = NULL;
	platform2 = NULL;
	meleeEnemy = NULL;
	camera = NULL;
}

Gameplay::~Gameplay()
{
	if (player) delete player;
	if (platform) delete platform;
	if (platform2) delete platform2;
	if (meleeEnemy) delete meleeEnemy;
	if (camera) delete camera;
}

void Gameplay::init(RenderWindow* &window)
{
	player = new Player();
	platform = new Platform(SCREEN_WIDTH / 2 - 200, SCREEN_HEIGHT / 2, 300, 150, Color::White);
	platform2 = new Platform(SCREEN_WIDTH / 2 + 150, SCREEN_HEIGHT / 2, 150, 100, Color::White);
	meleeEnemy = new MeleeEnemy();
	camera = new View({ player->getCenterX(), player->getCenterY() - SCREEN_HEIGHT / 4.0f }, { static_cast<float>(SCREEN_WIDTH), static_cast<float>(SCREEN_HEIGHT) });

	window->setView(*camera);
}

void Gameplay::update(RenderWindow* &window)
{
	if (player)
	{
		player->checkKeyPressedInput();
		player->checkKeyDownInput(window);
		player->checkKeyReleasedInput();
		player->updatePosition();
		checkGameplayColls(platform);
		checkGameplayColls(platform2);
		player->updateMovement();
	}

	if (meleeEnemy)
	{
		meleeEnemy->updatePos(player->getRec(), platform->getRec());

		if (meleeEnemy->getRec().getPosition().y>SCREEN_HEIGHT)
		{
			delete meleeEnemy;
			meleeEnemy = NULL;
		}
	}

	camera->setCenter(player->getCenterX(), player->getCenterY() - SCREEN_HEIGHT / 4.0f);
	window->setView(*camera);
}

void Gameplay::draw(RenderWindow* &window)
{
	window->clear();
	window->draw(platform->getRec());
	window->draw(platform2->getRec());
	window->draw(player->getRec());
	if(meleeEnemy)window->draw(meleeEnemy->getRec());
	window->display();
}

void Gameplay::close()
{

}

float Gameplay::getCollisionMargin(float jumpingSpeed)
{
	return jumpingSpeed / 2;
}

void Gameplay::checkGameplayColls(Platform* plat)
{
	switch (plat->checkSideProximity(player->getRec(), getCollisionMargin(player->getJumpingSpeed())))
	{
	case Top:
		if (player->colliding(plat->getRec()))
		{
			player->setJumpState(onGround);
			player->setRecY(plat->getUpperSide() - player->getRec().getSize().y);
		}
		break;
	case Bottom:
		if (player->colliding(plat->getRec()))
		{
			player->setSpeedY(0);
			player->setRecY(plat->getBottomSide());
		}
		break;
	case Right:
		if (player->colliding(plat->getRec()))
		{
			player->setSpeedX(0);
			player->setRecX(plat->getRightSide());
		}
		break;
	case Left:
		if (player->colliding(plat->getRec()))
		{
			player->setSpeedX(0);
			player->setRecX(plat->getLeftSide() - player->getRec().getSize().x);
		}
		break;
	}

	if (player->fallingOffPlatform(plat))
	{
		player->setJumpState(falling);
	}

	player->checkScreenLimits();
	//meleeEnemy->checkScreenLimits();
}