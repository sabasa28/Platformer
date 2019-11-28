#include "gameplay.h"

#include "general/game.h"

Gameplay::Gameplay()
{
	for (int y = 0; y < PLATFORM_GRID_HEIGHT; y++)
	{
		for (int x = 0; x < PLATFORM_GRID_WIDTH; x++)
		{
			platformGrid[y][x] = NULL;
		}
	}
	for (int y = 0; y < PLATFORM_GRID_HEIGHT; y++)
	{
		for (int x = 0; x < PLATFORM_GRID_WIDTH; x++)
		{
			switch (y)
			{
			case 0: if (x == 3)
				platformGrid[y][x] = new Platform(x, y); break;
			case 1: if (x == 5)
				platformGrid[y][x] = new Platform(x, y); break;
			case 2: if (x == 2 || x == 7)
				platformGrid[y][x] = new Platform(x, y); break;
			case 3: if (x >= 0 && x < 6)
				platformGrid[y][x] = new Platform(x, y); break;
			case 4: break;
			case 5: if (x >= 0 && x < PLATFORM_GRID_WIDTH)
				platformGrid[y][x] = new Platform(x, y); break;
			default: break;
			}
		}
	}

	player = new Player();

	for (int i = 0; i < ENEMY_AMMOUNT; i++)
	{
		meleeEnemy[i] = NULL;
	}
	for (int i = 0; i < ENEMY_AMMOUNT; i++)
	{
		meleeEnemy[i] = new MeleeEnemy();
	}
	meleeEnemy[0]->setRecX(100);
	meleeEnemy[1]->setRecX(400);

	goal = new RectangleShape({ 50, 50 });
	goal->setPosition({ PLATFORM_SIZE * 10, PLATFORM_SIZE * (PLATFORM_GRID_HEIGHT - 1) - goal->getGlobalBounds().height });
	goal->setFillColor(Color::Yellow);

	camera = new View({ player->getCenterX(), player->getCenterY() - SCREEN_HEIGHT / 4.0f }, { static_cast<float>(SCREEN_WIDTH), static_cast<float>(SCREEN_HEIGHT) });
	Game::window->setView(*camera);
}

Gameplay::~Gameplay()
{
	for (int y = 0; y < PLATFORM_GRID_HEIGHT; y++)
	{
		for (int x = 0; x < PLATFORM_GRID_WIDTH; x++)
		{
			if (platformGrid[y][x]) delete platformGrid[y][x];
		}
	}

	if (player) delete player;

	for (int i = 0; i < ENEMY_AMMOUNT; i++)
	{
		if (meleeEnemy[i]) delete meleeEnemy[i];
	}

	if (camera) delete camera;

	if (goal) delete goal;
}

void Gameplay::update()
{
	if (player)
	{
		player->checkKeyPressedInput();
		player->checkKeyDownInput();
		player->checkKeyReleasedInput();
		player->updatePosition();

		checkGameplayColls();

		for (int y = 0; y < PLATFORM_GRID_HEIGHT; y++)
		{
			for (int x = 0; x < PLATFORM_GRID_WIDTH; x++)
			{
				if (platformGrid[y][x])
				{
					checkGameplayColls2(platformGrid[y][x]);
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
			for (int y = 0; y < PLATFORM_GRID_HEIGHT; y++)
			{
				for (int x = 0; x < PLATFORM_GRID_WIDTH; x++)
				{
					if (platformGrid[y][x])
					{
						if (meleeEnemy[i]->getRec().getGlobalBounds().intersects(platformGrid[y][x]->getRec().getGlobalBounds()))
						{
							switch (platformGrid[y][x]->checkSideProximity(meleeEnemy[i]->getRec(), 5))
							{
							case Top:
								aux = true;
								meleeEnemy[i]->setRecY(platformGrid[y][x]->getRec().getPosition().y - meleeEnemy[i]->getRec().getSize().y);
								break;
							case Right:
								meleeEnemy[i]->setSpeed({ 0.0f, meleeEnemy[i]->getSpeed().y });
								meleeEnemy[i]->setRecX(platformGrid[y][x]->getRec().getPosition().x + platformGrid[y][x]->getRec().getSize().x);
								cout << "right" << endl;
								break;
							case Left:
								meleeEnemy[i]->setSpeed({ 0.0f, meleeEnemy[i]->getSpeed().y });
								meleeEnemy[i]->setRecX(platformGrid[y][x]->getRec().getPosition().x - meleeEnemy[i]->getRec().getSize().x);
								cout << "left" << endl;
								break;
							case Bottom:
								meleeEnemy[i]->setSpeed({ meleeEnemy[i]->getSpeed().x, 0.0f });
								meleeEnemy[i]->setRecY(platformGrid[y][x]->getRec().getPosition().y + platformGrid[y][x]->getRec().getSize().y);
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
	Game::window->setView(*camera);
}

void Gameplay::draw()
{
	for (int y = 0; y < PLATFORM_GRID_HEIGHT; y++)
	{
		for (int x = 0; x < PLATFORM_GRID_WIDTH; x++)
		{
			if (platformGrid[y][x])
			{
				Game::window->draw(platformGrid[y][x]->getRec());
			}
		}
	}
	Game::window->draw(player->getRec());
	for (int i = 0; i < ENEMY_AMMOUNT; i++)
	{
		if(meleeEnemy[i])Game::window->draw(meleeEnemy[i]->getRec());
	}

	Game::window->draw(*goal);
}

float Gameplay::getCollisionMargin(float jumpingSpeed)
{
	return jumpingSpeed / 3;
}

void Gameplay::checkGameplayColls()
{
	for (int y = 0; y < PLATFORM_GRID_HEIGHT; y++)
	{
		for (int x = 0; x < PLATFORM_GRID_WIDTH; x++)
		{
			if (platformGrid[y][x])
			{
				platformGrid[y][x]->setRelativePlayerJumpState(falling_relative);

				if (player->colliding(platformGrid[y][x]->getRec()))
				{
					switch (platformGrid[y][x]->checkSideProximity(player->getRec(), getCollisionMargin(player->getJumpingSpeed())))
					{
					case Top:
						cout << "onground";
						platformGrid[y][x]->setRelativePlayerJumpState(onGround_relative);
						player->setJumpState(onGround);
						player->setRecY(platformGrid[y][x]->getUpperSide() - player->getRec().getSize().y);
						break;
					case Bottom:
						player->setSpeedY(0);
						player->setRecY(platformGrid[y][x]->getBottomSide());
						break;
					case Right:
						player->setSpeedX(0);
						player->setRecX(platformGrid[y][x]->getRightSide());
						break;
					case Left:
						player->setSpeedX(0);
						player->setRecX(platformGrid[y][x]->getLeftSide() - player->getRec().getSize().x);
						break;
					}
				}
			}
		}
	}
	

	for (int i = 0; i < ENEMY_AMMOUNT; i++)
	{
		if (player->colliding(meleeEnemy[i]->getRec()))
		{
			Game::changeGamestate(gameOver_state);
		}
	}

	if (player->colliding(*goal))
	{
		Game::changeGamestate(gameOver_state);
	}

	player->checkScreenLimits();
}

void Gameplay::checkGameplayColls2(Platform* plat)
{
	bool OnAnyPlatform = false;
	for (int y = 0; y < PLATFORM_GRID_HEIGHT; y++)
	{
		for (int x = 0; x < PLATFORM_GRID_WIDTH; x++)
		{
			if (platformGrid[y][x])
			{
				if (platformGrid[y][x]->getRelativePlayerJumpState() == onGround)
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