#include "gameplay.h"

#include "general/game.h"

Gameplay::Gameplay()
{
	for (int y = 0; y < PLATFORM_GRID_HEIGHT; y++)
	{
		for (int x = 0; x < PLATFORM_GRID_WIDTH; x++)
		{
			platformGrid[y][x] = NULL;
			
			switch (y)
			{
			case 2:
				//if (x >= 1)
				if (x == 1)
				{
					platformGrid[y][x] = new Platform(x, y);
				}
				break;
			case 4:
				if (x == 4)
				{
					platformGrid[y][x] = new Platform(x, y);
				}
				break;
			case 5:
				if (x == 8)
				{
					platformGrid[y][x] = new Platform(x, y);
				}
				break;
			case 6:
				if (x == 2)
				{
					platformGrid[y][x] = new Platform(x, y);
				}
				break;
			case 8:
				if (x == 4)
				{
					platformGrid[y][x] = new Platform(x, y);
				}
				break;
			case 9:
				if (x == 9)
				{
					platformGrid[y][x] = new Platform(x, y);
				}
				break;
			case 11:
				if (x == 9)
				{
					platformGrid[y][x] = new Platform(x, y);
				}
				break;
			case 12:
				if (x == 6)
				{
					platformGrid[y][x] = new Platform(x, y);
				}
				break;
			case 14:
				if (x == 2)
				{
					platformGrid[y][x] = new Platform(x, y);
				}
				if (x == 9)
				{
					platformGrid[y][x] = new Platform(x, y);
				}
				break;
			case 15:
				if (x == 15)
				{
					platformGrid[y][x] = new Platform(x, y);
				}
				if (x == 16)
				{
					platformGrid[y][x] = new Platform(x, y);
				}
				if (x == 17)
				{
					platformGrid[y][x] = new Platform(x, y);
				}
				break;
			case 16:
				if (x == 4)
				{
					platformGrid[y][x] = new Platform(x, y);
				}
				if (x == 14)
				{
					platformGrid[y][x] = new Platform(x, y);
				}
				if (x == 18)
				{
					platformGrid[y][x] = new Platform(x, y);
				}
				break;
			case 17:
				if (x == 4)
				{
					platformGrid[y][x] = new Platform(x, y);
				}
				break;
			case 19:
				if (x == 15)
				{
					platformGrid[y][x] = new Platform(x, y);
				}
				if (x == 17)
				if (x > 14 && x < 20)
				{
					platformGrid[y][x] = new Platform(x, y);
				}
				break;

			default: break;
			}
		}
	}
	backgroundTexture.loadFromFile("images/backgroundRock.png");
	backgroundTextureRect = new IntRect(0, 0, PLATFORM_SPRITE_SIZE, PLATFORM_SPRITE_SIZE);
	backgroundSprite.setTexture(backgroundTexture);
	backgroundSprite.setTextureRect(*backgroundTextureRect);

	player = new Player();

	for (int i = 0; i < ENEMY_AMMOUNT; i++)
	{
		meleeEnemy[i] = NULL;
	}

	meleeEnemy[0] = new MeleeEnemy({ 400.0f, -200.0f });
	meleeEnemy[1] = new MeleeEnemy({ 400.0f, 100.0f });
	meleeEnemy[2] = new MeleeEnemy({ 900.0f, -800.0f });

	goal = new RectangleShape({ static_cast<float>(GOAL_SIZE), static_cast<float>(GOAL_SIZE) });
	goal->setPosition({ 1600.0f + goal->getGlobalBounds().width/2 , -1000.0f });
	goal->setFillColor(Color::Yellow);
	goalTexture.loadFromFile("images/coin.png");
	goalTextureRect = new IntRect(0, 0, GOAL_SPRITE_SIZE, GOAL_SPRITE_SIZE);
	goalSprite.setTexture(goalTexture);
	goalSprite.setTextureRect(*goalTextureRect);
	goalSprite.setPosition(goal->getPosition().x - (GOAL_SPRITE_SIZE - GOAL_SIZE) / 2, goal->getPosition().y);

	camera = new View({ player->getCenterX(), player->getCenterY() - SCREEN_HEIGHT / 6.0f }, { static_cast<float>(SCREEN_WIDTH), static_cast<float>(SCREEN_HEIGHT) });
	Game::window->setView(*camera);

	Game::gameplayMusic.play();
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

	if (goal) delete goal;

	if (camera) delete camera;
	Game::window->setView(Game::window->getDefaultView());

	Game::gameplayMusic.stop();
}

void Gameplay::update()
{
	if (player)
	{
		player->setLastFrameAction(player->getCurrentAction());
		player->checkKeyPressedInput();
		player->checkKeyDownInput();
		player->checkKeyReleasedInput();
		player->updatePosition();

		checkGameplayColls(platformGrid);

		player->updateMovement();
		player->updateSprite();
	}

	for (int i = 0; i < ENEMY_AMMOUNT; i++)
	{
		if (meleeEnemy[i])
		{
			meleeEnemy[i]->updatePos(player->getRec());
			meleeEnemy[i]->updateCharginState();

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
								meleeEnemy[i]->setRecY(platformGrid[y][x]->getUpperSide() - meleeEnemy[i]->getRec().getSize().y);
								break;
							case Right:
								meleeEnemy[i]->setSpeed({ 0.0f, meleeEnemy[i]->getSpeed().y });
								meleeEnemy[i]->setRecX(platformGrid[y][x]->getRightSide());
								break;
							case Left:
								meleeEnemy[i]->setSpeed({ 0.0f, meleeEnemy[i]->getSpeed().y });
								meleeEnemy[i]->setRecX(platformGrid[y][x]->getLeftSide() - meleeEnemy[i]->getRec().getSize().x);
								break;
							case Bottom:
								meleeEnemy[i]->setSpeed({ meleeEnemy[i]->getSpeed().x, 0.0f });
								meleeEnemy[i]->setRecY(platformGrid[y][x]->getBottomSide());
							default:
								break;
							}
						}
					}
				}
			}

			meleeEnemy[i]->setOnGround(aux);

			if (meleeEnemy[i]->getUpperSide() > SCREEN_HEIGHT)
			{
				delete meleeEnemy[i];
				meleeEnemy[i] = NULL;
			}

			if (meleeEnemy[i])
			{
				meleeEnemy[i]->updateSprite();
			}
		}
	}

	if (camera)
	{
		camera->setCenter(player->getCenterX(), player->getCenterY() - SCREEN_HEIGHT / 8.0f);
		Game::window->setView(*camera);
	}
}

void Gameplay::draw()
{

	for (int y = 0; y < PLATFORM_GRID_HEIGHT; y++)
	{
		for (int x = 0; x < PLATFORM_GRID_WIDTH; x++)
		{
			drawBackground(x, y);
		}
	}

	for (int y = 0; y < PLATFORM_GRID_HEIGHT; y++)
	{
		for (int x = 0; x < PLATFORM_GRID_WIDTH; x++)
		{

			if (platformGrid[y][x])
			{
				//Game::window->draw(platformGrid[y][x]->getRec());
				Game::window->draw(platformGrid[y][x]->getSprite());
			}
		}
	}

	if (player) 
	{
		//Game::window->draw(player->getRec());
		Game::window->draw(player->getSprite());
	}

	for (int i = 0; i < ENEMY_AMMOUNT; i++)
	{
		//if (meleeEnemy[i]) Game::window->draw(meleeEnemy[i]->getRec());
		if (meleeEnemy[i]) Game::window->draw(meleeEnemy[i]->getSprite());
	}

	if (goal) Game::window->draw(goalSprite);
}

float Gameplay::getCollisionMargin(float jumpingSpeed)
{
	return jumpingSpeed / 3;
}

void Gameplay::checkGameplayColls(Platform* plat[][PLATFORM_GRID_WIDTH])
{

	if (player)
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
			if (meleeEnemy[i])
			{
				if (player->colliding(meleeEnemy[i]->getRec()))
				{
					Game::currentGameState=gameOver_state;
				}
			}
		}

		if (goal)
		{
			if (player->colliding(*goal))
			{
				Game::currentGameState=victory_state;
			}
		}
	}

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

	for (int y = 0; y < PLATFORM_GRID_HEIGHT; y++)
	{
		for (int x = 0; x < PLATFORM_GRID_WIDTH; x++)
		{
			if (platformGrid[y][x])
			{
				if (player)
				{
					if (player->fallingOffPlatform(plat[y][x]) && OnAnyPlatform == false && player->getJumpState() != start)
					{
						player->setJumpState(falling);
					}
				}
			}
		}
	}
}

void Gameplay::drawBackground(int x, int y)
{
	backgroundSprite.setPosition(static_cast<float>(PLATFORM_SIZE) * x, PLATFORM_MIN_Y_POS - static_cast<float>(PLATFORM_SIZE) * y);
	Game::window->draw(backgroundSprite);
}