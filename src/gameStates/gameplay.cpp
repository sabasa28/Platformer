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
			if ((x == 3 || x == 5) && (y == 2 || y==3))
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

		for (int y = 0; y < PLATFORMS_HEIGHT; y++)
		{
			for (int x = 0; x < PLATFORMS_WIDTH; x++)
			{
				if (platforms[x][y])
				{
					checkGameplayColls2(platforms[x][y]);
				}
			}
		}

		player->updateMovement();
	}


	if (meleeEnemy)
	{
		
		meleeEnemy->updatePos(player->getRec());
		
		bool aux=false;
		for (int y = 0; y < PLATFORMS_HEIGHT; y++)
		{
			for (int x = 0; x < PLATFORMS_WIDTH; x++)
			{
				if (platforms[x][y])
				{
					if (meleeEnemy->getRec().getGlobalBounds().intersects(platforms[x][y]->getRec().getGlobalBounds()))
					{
						switch (platforms[x][y]->checkSideProximity(meleeEnemy->getRec(), 5))
						{
						case Top:
							aux = true;
							meleeEnemy->setRecY(platforms[x][y]->getRec().getPosition().y - meleeEnemy->getRec().getSize().y);
							break;
						case Right:
							meleeEnemy->setSpeed({ 0.0f, meleeEnemy->getSpeed().y });
							meleeEnemy->setRecX(platforms[x][y]->getRec().getPosition().x + platforms[x][y]->getRec().getSize().x);
							cout << "right"<<endl;
							break;
						case Left:
							meleeEnemy->setSpeed({ 0.0f, meleeEnemy->getSpeed().y });
							meleeEnemy->setRecX(platforms[x][y]->getRec().getPosition().x - meleeEnemy->getRec().getSize().x);
							cout << "left" << endl;
							break;
						case Bottom:
							meleeEnemy->setSpeed({ meleeEnemy->getSpeed().x, 0.0f });
							meleeEnemy->setRecY(platforms[x][y]->getRec().getPosition().y + platforms[x][y]->getRec().getSize().y);
						default:
							break;
						}
					}
				}
			}
		}

		meleeEnemy->setOnGround(aux);

		if (meleeEnemy->getRec().getPosition().y > SCREEN_HEIGHT)
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
	if (player->colliding(plat->getRec()))
	{
		switch (plat->checkSideProximity(player->getRec(), getCollisionMargin(player->getJumpingSpeed())))
		{
		case Top:
			cout << "onground";
			jumpstatePlatform[x][y] = onGround;
			player->setJumpState(onGround);
			player->setRecY(plat->getUpperSide() - player->getRec().getSize().y);
			break;
		case Bottom:
			player->setSpeedY(0);
			player->setRecY(plat->getBottomSide());
			break;
		case Right:
			player->setSpeedX(0);
			player->setRecX(plat->getRightSide());
			break;
		case Left:
			player->setSpeedX(0);
			player->setRecX(plat->getLeftSide() - player->getRec().getSize().x);
			break;
		}
	}

	if (meleeEnemy&&player->getRightSide()>meleeEnemy->getLeftSide()&&player->getLeftSide()<meleeEnemy->getRightSide()&&player->getUpperSide()<meleeEnemy->getBottomSide()&&player->getBottomSide()>meleeEnemy->getUpperSide())
	{
		Game::changeGamestate(gameOver_state);
	}


	player->checkScreenLimits();
}

void Gameplay::checkGameplayColls2(Platform* plat)
{
	bool OnAnyPlatform = false;
	for (int i = 0; i < PLATFORMS_HEIGHT; i++)
	{
		for (int j = 0; j < PLATFORMS_WIDTH; j++)
		{
			if (platforms[i][j])
			{
				if (jumpstatePlatform[i][j] == onGround)
				{
					OnAnyPlatform = true;
				}
			}
		}
	}
	if (player->fallingOffPlatform(plat) && OnAnyPlatform==false && player->getJumpState() != start)
	{
		player->setJumpState(falling);
	}
}