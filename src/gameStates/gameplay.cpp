#include "gameplay.h"

#include "general/game.h"

Gameplay::Gameplay()
{
	player = NULL;
	meleeEnemy = NULL;
	for (int y = 0; y < PLATFORMS_HEIGHT; y++)
	{
		for (int x = 0; x < PLATFORMS_WIDTH; x++)
		{
			platforms[x][y] = NULL;
			jumpstatePlatform[x][y] = falling;
		}
	}
	camera = NULL;
}

Gameplay::~Gameplay()
{
	if (player) delete player;
	if (meleeEnemy) delete meleeEnemy;
	for (int y = 0; y < PLATFORMS_HEIGHT; y++)
	{
		for (int x = 0; x < PLATFORMS_WIDTH; x++)
		{
			if (platforms[x][y]) delete platforms[x][y];
		}
	}
	if (camera) delete camera;
}

void Gameplay::init(RenderWindow* &window)
{
	for (int y = 0; y < PLATFORMS_HEIGHT; y++)
	{
		for (int x = 0; x < PLATFORMS_WIDTH; x++)
		{
			if ((x == 1 || x == 2) && y == 2)
			{
				platforms[x][y] = new Platform(static_cast<float>(PLATFORM_SIZE) * x, static_cast<float>(PLATFORM_SIZE) * y, static_cast<float>(PLATFORM_SIZE), static_cast<float>(PLATFORM_SIZE), Color::White);
				jumpstatePlatform[x][y] = falling;
			}
		}
	}
	player = new Player();
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

		for (int y = 0; y < PLATFORMS_HEIGHT; y++)
		{
			for (int x = 0; x < PLATFORMS_WIDTH; x++)
			{
				if (platforms[x][y])
				{
					jumpstatePlatform[x][y] = falling;
					checkGameplayColls(platforms[x][y],x,y);
				}
			}
		}

		player->updateMovement();
	}

	if (meleeEnemy)
	{
		for (int y = 0; y < PLATFORMS_HEIGHT; y++)
		{
			for (int x = 0; x < PLATFORMS_WIDTH; x++)
			{
				if (platforms[x][y])
				{
					meleeEnemy->updatePos(player->getRec(), platforms[x][y]->getRec());
				}
			}
		}

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
	for (int y = 0; y < PLATFORMS_HEIGHT; y++)
	{
		for (int x = 0; x < PLATFORMS_WIDTH; x++)
		{
			if (platforms[x][y])
			{
				window->draw(platforms[x][y]->getRec());
			}
		}
	}
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

void Gameplay::checkGameplayColls(Platform* plat, int x, int y)
{
	switch (plat->checkSideProximity(player->getRec(), getCollisionMargin(player->getJumpingSpeed())))
	{
	case Top:
		if (player->colliding(plat->getRec()))
		{
			jumpstatePlatform[x][y] = onGround;
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

	if (meleeEnemy&&player->getRightSide()>meleeEnemy->getLeftSide()&&player->getLeftSide()<meleeEnemy->getRightSide()&&player->getUpperSide()<meleeEnemy->getBottomSide()&&player->getBottomSide()>meleeEnemy->getUpperSide())
	{
		Game::changeGamestate(gameOver_state);
	}

	if (player->fallingOffPlatform(plat) && jumpstatePlatform[x][y] != onGround)
	{
		player->setJumpState(falling);
	}

	player->checkScreenLimits();
	//meleeEnemy->checkScreenLimits();
}