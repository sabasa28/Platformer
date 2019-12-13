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

Gameplay::Gameplay(bool firstexecution)
{
	pauseButtonPressed = false;
	muteButtonPressed = false;
	controlsButtonPressed = false;


	for (int y = 0; y < GRID_HEIGHT; y++)
	{
		for (int x = 0; x < GRID_WIDTH; x++)
		{
			platformGrid[y][x] = NULL;

			switch (y)
			{
			case 22:
				if (x > 30 && x < 43)
				{
					platformGrid[y][x] = new Platform(x, y);
				}
				break;
			case 23:
				if (x == 36|| x == 43 || x == 44 || x == 48)
				{
					platformGrid[y][x] = new Platform(x, y);
				}
				break;
			case 24:
				if (x == 34 || x == 36 || x == 37 || x == 39 || x==49 || x == 61
					|| x == 62 || x == 63 || x == 66 || x == 70|| (x >= 74 && x <= 80))
				{
					platformGrid[y][x] = new Platform(x, y);
				}
				break;
			case 25:
				if (x == 33 || x == 36 || x == 39 || x == 58 || x == 80)
				{
					platformGrid[y][x] = new Platform(x, y);
				}
				break;
			case 26:
				if (x == 36 || x == 39|| x == 49 || x == 56 || x == 76 || x == 78 || x == 80)
				{
					platformGrid[y][x] = new Platform(x, y);
				}
				break;
			case 27:
				if (x == 36 || x == 39 || x == 54 || x == 76 || x == 80)
				{
					platformGrid[y][x] = new Platform(x, y);
				}
				break;
			case 28:
				if (x == 39 || x == 47 || x == 52 || x == 76 || x == 80)
				{
					platformGrid[y][x] = new Platform(x, y);
				}
				break;
			case 29:
				if (x == 39 || x == 50 || x == 80)
				{
					platformGrid[y][x] = new Platform(x, y);
				}
				break;
			case 30:
				if (x == 39)
				{
					platformGrid[y][x] = new Platform(x, y);
				}
				break;
			case 31:
				if (x == 83)
				{
					platformGrid[y][x] = new Platform(x, y);
				}
				break;
			case 33:
				if (x == 86)
				{
					platformGrid[y][x] = new Platform(x, y);
				}
				break;
			case 34:
				if ((x > 89 && x < 93))
				{
					platformGrid[y][x] = new Platform(x, y);
				}
				break;
			case 35:
				if (x == 89 || x == 93)
				{
					platformGrid[y][x] = new Platform(x, y);
				}
				break;
			case 37:
				if (x == 90 || x == 92)
				{
					platformGrid[y][x] = new Platform(x, y);
				}
				break;
			default:
				break;
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
		slimeBlock[i] = NULL;
	}
	slimeBlock[0] = new SlimeBlock({ 4725.0f, -2200.0f });
	slimeBlock[1] = new SlimeBlock({ 3800.0f, -1700.0f });
	slimeBlock[2] = new SlimeBlock({ 7825.0f, -1900.0f });
	slimeBlock[3] = new SlimeBlock({ 8600.0f, -2800.0f });

	goldCoin = new GoldCoin();

	paused = false;
	showControls = firstexecution;
	
	camera = new View({ player->getCenterX(), player->getCenterY() - SCREEN_HEIGHT / 8.0f }, { static_cast<float>(SCREEN_WIDTH), static_cast<float>(SCREEN_HEIGHT) });

	pause = new Pause(camera);

	controls = new Controls(camera);

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
		if (slimeBlock[i]) delete slimeBlock[i];
	}

	if (goldCoin) delete goldCoin;

	if (camera) delete camera;

	if (pause) delete pause;

	if (controls) delete controls;

	if (backgroundTextureRect) delete backgroundTextureRect;

	Game::window->setView(Game::window->getDefaultView());
	Game::gameplayMusic.stop();
}

void Gameplay::checkKeyDownInput()
{
	if (!controlsButtonPressed)
	{
		if (Keyboard::isKeyPressed(Keyboard::O) && !paused)
		{
			showControls = !showControls;

			controlsButtonPressed = true;
		}
	}
	else
	{
		if (!Keyboard::isKeyPressed(Keyboard::O))
		{
			controlsButtonPressed = false;
		}
	}

	if (!pauseButtonPressed)
	{
		if ((Keyboard::isKeyPressed(Keyboard::P) || Keyboard::isKeyPressed(Keyboard::Escape))&& !showControls)
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
				if (!Game::getAudioMuted())
				{
					Game::buttonSFX.play();
				}
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
						switch (platformGrid[y][x]->checkSideProximity(player->getRec(), player->getCollisionMargin(),false))
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
			if (slimeBlock[i])
			{
				if (player->colliding(slimeBlock[i]->getRec()))
				{
					if (!Game::getAudioMuted())
					{
						Game::impactSFX.play();
					}
					Game::currentGameState = gameOver_state;
				}
			}
		}

		if (goldCoin)
		{
			if (player->colliding(goldCoin->getRec()))
			{
				if (!Game::getAudioMuted())
				{
					Gameplay::coinsSFX.play();
				}
				Game::currentGameState = victory_state;
			}
		}

		if (player->getUpperSide() > FALL_LIMIT)
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

void Gameplay::update()
{
	checkKeyDownInput();

	if (!paused && !showControls)
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
			if (slimeBlock[i])
			{
				slimeBlock[i]->updatePos(player->getRec());
				slimeBlock[i]->updateCharginState();

				bool aux = false;
				for (int y = 0; y < GRID_HEIGHT; y++)
				{
					for (int x = 0; x < GRID_WIDTH; x++)
					{
						if (platformGrid[y][x])
						{
							if (slimeBlock[i]->getRec().getGlobalBounds().intersects(platformGrid[y][x]->getRec().getGlobalBounds()))
							{
								switch (platformGrid[y][x]->checkSideProximity(slimeBlock[i]->getRec(), slimeBlock[i]->getCollisionMargin(), true))
								{
								case Top:
									aux = true;
									slimeBlock[i]->setRecPosY(platformGrid[y][x]->getUpperSide() - slimeBlock[i]->getRec().getSize().y);
									break;
								case Right:
									slimeBlock[i]->setSpeed({ 0.0f, slimeBlock[i]->getSpeed().y });
									slimeBlock[i]->setRecPosX(platformGrid[y][x]->getRightSide());
									break;
								case Left:
									slimeBlock[i]->setSpeed({ 0.0f, slimeBlock[i]->getSpeed().y });
									slimeBlock[i]->setRecPosX(platformGrid[y][x]->getLeftSide() - slimeBlock[i]->getRec().getSize().x);
									break;
								case Bottom:
									slimeBlock[i]->setSpeed({ slimeBlock[i]->getSpeed().x, 0.0f });
									slimeBlock[i]->setRecPosY(platformGrid[y][x]->getBottomSide());
								default:
									break;
								}
							}
						}
					}
				}

				slimeBlock[i]->setOnGround(aux);

				if (slimeBlock[i]->getUpperSide() > SCREEN_HEIGHT)
				{
					delete slimeBlock[i];
					slimeBlock[i] = NULL;
				}

				if (slimeBlock[i])
				{
					slimeBlock[i]->updateSprite();
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
		if (pause) pause->center(camera);
		if (controls) controls->center(camera);
	}

	if (!muteButtonPressed)
	{
		if (Keyboard::isKeyPressed(Keyboard::M))
		{
			Game::buttonSFX.play();
			Game::setAudioMuted(!Game::getAudioMuted());
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
	backgroundSprite.setPosition(BACKGROUND_TILE_SIZE * x, BACKGROUND_MIN_POS - BACKGROUND_TILE_SIZE * y);
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
		if (slimeBlock[i]) Game::window->draw(slimeBlock[i]->getSprite());
	}

	if (goldCoin) Game::window->draw(goldCoin->getSprite());

	if (paused)
	{
		if(pause) pause->draw();
	}

	if (showControls)
	{
		if (controls) controls->draw();
	}
}
}