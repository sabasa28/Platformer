#include "gameplay.h"

#include "general/game.h"

namespace game
{
SoundBuffer Gameplay::footstepSFXBuffer;
Sound Gameplay::footstepSFX;
SoundBuffer Gameplay::jumpSFXBuffer;
Sound Gameplay::jumpSFX;
SoundBuffer Gameplay::coinsSFXBuffer;
Sound Gameplay::coinsSFX;

static float getCollisionMargin(float jumpingSpeed)
{
	return jumpingSpeed / 3;
}

Gameplay::Gameplay()
{
	pauseButtonPressed = false;
	muteButtonPressed = false;

	for (int y = 0; y < GRID_HEIGHT; y++)
	{
		for (int x = 0; x < GRID_WIDTH; x++)
		{
			platformGrid[y][x] = NULL;

			switch (y)
			{
			case 2:
				if (x == 11)
				{
					platformGrid[y][x] = new Platform(x, y);
				}
				break;
			case 4:
				if (x == 14)
				{
					platformGrid[y][x] = new Platform(x, y);
				}
				break;
			case 5:
				if (x == 18)
				{
					platformGrid[y][x] = new Platform(x, y);
				}
				break;
			case 6:
				if (x == 11)
				{
					platformGrid[y][x] = new Platform(x, y);
				}
				break;
			case 8:
				if (x == 14)
				{
					platformGrid[y][x] = new Platform(x, y);
				}
				break;
			case 9:
				if (x == 19)
				{
					platformGrid[y][x] = new Platform(x, y);
				}
				break;
			case 11:
				if (x == 19)
				{
					platformGrid[y][x] = new Platform(x, y);
				}
				break;
			case 13:
				if (x == 16)
				{
					platformGrid[y][x] = new Platform(x, y);
				}
				break;
			case 14:
				if (x == 12)
				{
					platformGrid[y][x] = new Platform(x, y);
				}
				if (x == 19)
				{
					platformGrid[y][x] = new Platform(x, y);
				}
				break;
			case 15:
				if (x == 25)
				{
					platformGrid[y][x] = new Platform(x, y);
				}
				if (x == 26)
				{
					platformGrid[y][x] = new Platform(x, y);
				}
				if (x == 27)
				{
					platformGrid[y][x] = new Platform(x, y);
				}
				break;
			case 16:
				if (x == 24)
				{
					platformGrid[y][x] = new Platform(x, y);
				}
				if (x == 28)
				{
					platformGrid[y][x] = new Platform(x, y);
				}
				break;
			case 17:
				if (x == 14)
				{
					platformGrid[y][x] = new Platform(x, y);
				}
				break;
			case 18:
				if (x == 14)
				{
					platformGrid[y][x] = new Platform(x, y);
				}
				break;
			case 19:
				if (x == 25)
				{
					platformGrid[y][x] = new Platform(x, y);
				}
				if (x == 27)
				{
					platformGrid[y][x] = new Platform(x, y);
				}
				break;

			default: break;
			}
		}
	}
	backgroundTexture.loadFromFile("images/backgroundRock.png");
	backgroundTextureRect = new IntRect(0, 0, 100, 100);
	backgroundSprite.setTexture(backgroundTexture);
	backgroundSprite.setTextureRect(*backgroundTextureRect);

	player = new Player();

	for (int i = 0; i < ENEMY_AMMOUNT; i++)
	{
		meleeEnemy[i] = NULL;
	}
	meleeEnemy[0] = new MeleeEnemy({ 1400.0f, -200.0f });
	meleeEnemy[1] = new MeleeEnemy({ 1400.0f, 100.0f });
	meleeEnemy[2] = new MeleeEnemy({ 1900.0f, -800.0f });

	goal = new RectangleShape({ static_cast<float>(GOAL_SIZE), static_cast<float>(GOAL_SIZE) });
	goal->setPosition({ 2600.0f + goal->getGlobalBounds().width/2 , -1000.0f });
	goal->setFillColor(Color::Yellow);
	goalTexture.loadFromFile("images/coin.png");
	goalTextureRect = new IntRect(0, 0, GOAL_SPRITE_SIZE, GOAL_SPRITE_SIZE);
	goalSprite.setTexture(goalTexture);
	goalSprite.setTextureRect(*goalTextureRect);
	goalSprite.setPosition(goal->getPosition().x - (GOAL_SPRITE_SIZE - GOAL_SIZE) / 2, goal->getPosition().y);

	paused = false;
	pauseRec.setSize(PAUSE_SIZE);
	pauseRec.setPosition(PAUSE_POS);
	pauseRec.setFillColor(Color::Black);
	for (int i = 0; i < PAUSE_TEXT_AMMOUNT; i++)
	{
		pauseTexts[i] = NULL;
	}
	pauseTexts[0] = new DisplayText("PAUSED", true, PAUSE_TEXT_Y, Color::Yellow, PAUSE_FONT_SIZE);
	pauseTexts[1] = new DisplayText("\"Enter\" to go back to menu", true, pauseTexts[0]->getBottomSide() + PAUSE_SPACE_BETWEEN_TEXT, Color::White, PAUSE_FONT_SIZE);
	pauseTexts[2] = new DisplayText("\"M\" to mute/unmute", true, pauseTexts[1]->getBottomSide() + PAUSE_SPACE_BETWEEN_TEXT, Color::White, PAUSE_FONT_SIZE);
	pauseTexts[3] = new DisplayText("\"Escape\" to unpause", true, pauseTexts[2]->getBottomSide() + PAUSE_SPACE_BETWEEN_TEXT, Color::White, PAUSE_FONT_SIZE);

	camera = new View({ player->getCenterX(), player->getCenterY() - SCREEN_HEIGHT / 6.0f }, { static_cast<float>(SCREEN_WIDTH), static_cast<float>(SCREEN_HEIGHT) });

	footstepSFXBuffer.loadFromFile("sounds/footstep.ogg");
	footstepSFX.setBuffer(footstepSFXBuffer);
	jumpSFXBuffer.loadFromFile("sounds/jump.ogg");
	jumpSFX.setBuffer(jumpSFXBuffer);
	coinsSFXBuffer.loadFromFile("sounds/coins.ogg");
	coinsSFX.setBuffer(coinsSFXBuffer);

	Game::window->setView(*camera);
	Game::gameplayMusic.play();
}

Gameplay::~Gameplay()
{
	for (int y = 0; y < GRID_HEIGHT; y++)
	{
		for (int x = 0; x < GRID_WIDTH; x++)
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

	for (int i = 0; i < PAUSE_TEXT_AMMOUNT; i++)
	{
		if (pauseTexts[i]) delete pauseTexts[i];
	}

	if (camera) delete camera;

	if (backgroundTextureRect) delete backgroundTextureRect;
	if (goalTextureRect) delete goalTextureRect;

	Game::window->setView(Game::window->getDefaultView());
	Game::gameplayMusic.stop();
}

void Gameplay::checkKeyDownInput()
{
	if (!pauseButtonPressed)
	{
		if (Keyboard::isKeyPressed(Keyboard::P) || Keyboard::isKeyPressed(Keyboard::Escape))
		{
			if (!paused)
			{
				paused = true;
			}
			else
			{
				paused = false;
			}

			pauseButtonPressed = true;
		}
	}
	else
	{
		if (!Keyboard::isKeyPressed(Keyboard::P) && !Keyboard::isKeyPressed(Keyboard::Escape))
		{
			pauseButtonPressed = false;
		}
	}

	if (paused)
	{
		if (Keyboard::isKeyPressed(Keyboard::Enter))
		{
			if (!Game::getGameStateInputActive())
			{
				Game::buttonSFX.play();
				Game::setGameStateInputActive(true);
				Game::currentGameState = menu_state;
			}
		}
		else
		{
			if (Game::getGameStateInputActive())
			{
				Game::setGameStateInputActive(false);
			}
		}
	}
}

void Gameplay::checkGameplayColls(Platform* plat[][GRID_WIDTH])
{
	if (player)
	{
		for (int y = 0; y < GRID_HEIGHT; y++)
		{
			for (int x = 0; x < GRID_WIDTH; x++)
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
							player->setRecPosY(platformGrid[y][x]->getUpperSide() - player->getRec().getSize().y);
							break;
						case Bottom:
							player->setSpeedY(0);
							player->setRecPosY(platformGrid[y][x]->getBottomSide());
							break;
						case Right:
							player->setSpeedX(0);
							player->setRecPosX(platformGrid[y][x]->getRightSide());
							break;
						case Left:
							player->setSpeedX(0);
							player->setRecPosX(platformGrid[y][x]->getLeftSide() - player->getRec().getSize().x);
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
					Game::impactSFX.play();
					Game::currentGameState = gameOver_state;
				}
			}
		}

		if (goal)
		{
			if (player->colliding(*goal))
			{
				Gameplay::coinsSFX.play();
				Game::currentGameState = victory_state;
			}
		}

		if (player->getUpperSide() > SCREEN_HEIGHT + player->getRec().getSize().y * 3)
		{
			Game::currentGameState = gameOver_state;
		}
	}

	bool OnAnyPlatform = false;
	for (int y = 0; y < GRID_HEIGHT; y++)
	{
		for (int x = 0; x < GRID_WIDTH; x++)
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

	for (int y = 0; y < GRID_HEIGHT; y++)
	{
		for (int x = 0; x < GRID_WIDTH; x++)
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

void Gameplay::setPause(bool state)
{
	paused = state;
}

bool Gameplay::getPause()
{
	return paused;
}

void Gameplay::centerPause()
{
	if (pauseTexts[0]) pauseTexts[0]->setPosition({ camera->getCenter().x - pauseTexts[0]->getTextWidth() / 2.0f, camera->getCenter().y - PAUSE_TEXT_Y });
	if (pauseTexts[1]) pauseTexts[1]->setPosition({ camera->getCenter().x - pauseTexts[1]->getTextWidth() / 2.0f, pauseTexts[0]->getBottomSide() + PAUSE_SPACE_BETWEEN_TEXT });
	if (pauseTexts[2]) pauseTexts[2]->setPosition({ camera->getCenter().x - pauseTexts[2]->getTextWidth() / 2.0f, pauseTexts[1]->getBottomSide() + PAUSE_SPACE_BETWEEN_TEXT });
	if (pauseTexts[3]) pauseTexts[3]->setPosition({ camera->getCenter().x - pauseTexts[3]->getTextWidth() / 2.0f, pauseTexts[2]->getBottomSide() + PAUSE_SPACE_BETWEEN_TEXT });

	pauseRec.setPosition({ camera->getCenter().x - PAUSE_SIZE.x / 2.0f, camera->getCenter().y - PAUSE_SIZE.y / 2.0f });
}

void Gameplay::update()
{
	checkKeyDownInput();

	if (!paused)
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
				for (int y = 0; y < GRID_HEIGHT; y++)
				{
					for (int x = 0; x < GRID_WIDTH; x++)
					{
						if (platformGrid[y][x])
						{
							if (meleeEnemy[i]->getRec().getGlobalBounds().intersects(platformGrid[y][x]->getRec().getGlobalBounds()))
							{
								switch (platformGrid[y][x]->checkSideProximity(meleeEnemy[i]->getRec(), 5))
								{
								case Top:
									aux = true;
									meleeEnemy[i]->setRecPosY(platformGrid[y][x]->getUpperSide() - meleeEnemy[i]->getRec().getSize().y);
									break;
								case Right:
									meleeEnemy[i]->setSpeed({ 0.0f, meleeEnemy[i]->getSpeed().y });
									meleeEnemy[i]->setRecPosX(platformGrid[y][x]->getRightSide());
									break;
								case Left:
									meleeEnemy[i]->setSpeed({ 0.0f, meleeEnemy[i]->getSpeed().y });
									meleeEnemy[i]->setRecPosX(platformGrid[y][x]->getLeftSide() - meleeEnemy[i]->getRec().getSize().x);
									break;
								case Bottom:
									meleeEnemy[i]->setSpeed({ meleeEnemy[i]->getSpeed().x, 0.0f });
									meleeEnemy[i]->setRecPosY(platformGrid[y][x]->getBottomSide());
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
	else
	{
		centerPause();
	}

	if (!muteButtonPressed)
	{
		if (Keyboard::isKeyPressed(Keyboard::M))
		{
			Game::buttonSFX.play();
			Game::switchMusicState();
			muteButtonPressed = true;
		}
	}
	else
	{
		if (!Keyboard::isKeyPressed(Keyboard::M))
		{
			muteButtonPressed = false;
		}
	}

}

void Gameplay::drawBackground(int x, int y)
{
	backgroundSprite.setPosition(100.0f * x, 700 - 100.0f * y);
	Game::window->draw(backgroundSprite);
}

void Gameplay::draw()
{
	for (int y = 0; y < GRID_HEIGHT; y++)
	{
		for (int x = 0; x < GRID_WIDTH; x++)
		{
			drawBackground(x, y);
		}
	}

	for (int y = 0; y < GRID_HEIGHT; y++)
	{
		for (int x = 0; x < GRID_WIDTH; x++)
		{

			if (platformGrid[y][x])
			{
				Game::window->draw(platformGrid[y][x]->getSprite());
			}
		}
	}

	if (player) 
	{
		Game::window->draw(player->getSprite());
	}

	for (int i = 0; i < ENEMY_AMMOUNT; i++)
	{
		if (meleeEnemy[i]) Game::window->draw(meleeEnemy[i]->getSprite());
	}

	if (goal) Game::window->draw(goalSprite);

	if (paused)
	{
		Game::window->draw(pauseRec);
		for (int i = 0; i < PAUSE_TEXT_AMMOUNT; i++)
		{
			if (pauseTexts[i]) pauseTexts[i]->draw();
		}
	}
}
}