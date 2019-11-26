#include "gameplay.h"

#include "general/game.h"

Gameplay::Gameplay()
{
	player = NULL;
	for (int i = 0; i < ENEMY_AMMOUNT; i++)
	{
		meleeEnemy[i] = NULL;
	}

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
	for (int i = 0; i < ENEMY_AMMOUNT; i++)
	{
		if (meleeEnemy[i]) delete meleeEnemy[i];
	}

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
			if ((x>=0 && x<6) && (y == 4))
			{
				platforms[x][y] = new Platform(static_cast<float>(PLATFORM_SIZE) * x, static_cast<float>(PLATFORM_SIZE) * y, static_cast<float>(PLATFORM_SIZE), static_cast<float>(PLATFORM_SIZE), Color::White);
				jumpstatePlatform[x][y] = falling;
			}
		}
	}

	platforms[2][3] = new Platform(static_cast<float>(PLATFORM_SIZE) * 2, static_cast<float>(PLATFORM_SIZE) * 3, static_cast<float>(PLATFORM_SIZE), static_cast<float>(PLATFORM_SIZE), Color::White);
	jumpstatePlatform[2][3] = falling;
	
	platforms[5][2] = new Platform(static_cast<float>(PLATFORM_SIZE) * 5, static_cast<float>(PLATFORM_SIZE) * 2, static_cast<float>(PLATFORM_SIZE), static_cast<float>(PLATFORM_SIZE), Color::White);
	jumpstatePlatform[5][2] = falling;
	
	platforms[3][1] = new Platform(static_cast<float>(PLATFORM_SIZE) * 3, static_cast<float>(PLATFORM_SIZE) * 1, static_cast<float>(PLATFORM_SIZE), static_cast<float>(PLATFORM_SIZE), Color::White);
	jumpstatePlatform[3][1] = falling;

	platforms[1][0] = new Platform(static_cast<float>(PLATFORM_SIZE) * 1, static_cast<float>(PLATFORM_SIZE) * 0, static_cast<float>(PLATFORM_SIZE), static_cast<float>(PLATFORM_SIZE), Color::White);
	jumpstatePlatform[1][0] = falling;



	player = new Player();

	for (int i = 0; i < ENEMY_AMMOUNT; i++)
	{
		meleeEnemy[i] = new MeleeEnemy();
	}
	meleeEnemy[0]->setRecX(100);
	meleeEnemy[1]->setRecX(400);

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

	for (int i = 0; i < ENEMY_AMMOUNT; i++)
	{
		if (meleeEnemy[i])
		{

			meleeEnemy[i]->updatePos(player->getRec());

			bool aux = false;
			for (int y = 0; y < PLATFORMS_HEIGHT; y++)
			{
				for (int x = 0; x < PLATFORMS_WIDTH; x++)
				{
					if (platforms[x][y])
					{
						if (meleeEnemy[i]->getRec().getGlobalBounds().intersects(platforms[x][y]->getRec().getGlobalBounds()))
						{
							switch (platforms[x][y]->checkSideProximity(meleeEnemy[i]->getRec(), 5))
							{
							case Top:
								aux = true;
								meleeEnemy[i]->setRecY(platforms[x][y]->getRec().getPosition().y - meleeEnemy[i]->getRec().getSize().y);
								break;
							case Right:
								meleeEnemy[i]->setSpeed({ 0.0f, meleeEnemy[i]->getSpeed().y });
								meleeEnemy[i]->setRecX(platforms[x][y]->getRec().getPosition().x + platforms[x][y]->getRec().getSize().x);
								cout << "right" << endl;
								break;
							case Left:
								meleeEnemy[i]->setSpeed({ 0.0f, meleeEnemy[i]->getSpeed().y });
								meleeEnemy[i]->setRecX(platforms[x][y]->getRec().getPosition().x - meleeEnemy[i]->getRec().getSize().x);
								cout << "left" << endl;
								break;
							case Bottom:
								meleeEnemy[i]->setSpeed({ meleeEnemy[i]->getSpeed().x, 0.0f });
								meleeEnemy[i]->setRecY(platforms[x][y]->getRec().getPosition().y + platforms[x][y]->getRec().getSize().y);
							default:
								break;
							}
						}
					}
				}
			}

			meleeEnemy[i]->setOnGround(aux);

			if (meleeEnemy[i]->getRec().getPosition().y > SCREEN_HEIGHT)
			{
				delete meleeEnemy[i];
				meleeEnemy[i] = NULL;
			}
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
	for (int i = 0; i < ENEMY_AMMOUNT; i++)
	{
		if(meleeEnemy[i])window->draw(meleeEnemy[i]->getRec());
	}

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
	for (int i = 0; i < ENEMY_AMMOUNT; i++)
	{
		if (meleeEnemy[i]&&player->getRightSide()>meleeEnemy[i]->getLeftSide()&&player->getLeftSide()<meleeEnemy[i]->getRightSide()&&player->getUpperSide()<meleeEnemy[i]->getBottomSide()&&player->getBottomSide()>meleeEnemy[i]->getUpperSide())
		{
			Game::changeGamestate(gameOver_state);
		}
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