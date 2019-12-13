#include "game.h"

namespace game
{
Event Game::event;
GameState Game::currentGameState = menu_state;
bool Game::gameStateInputActive = false;
bool Game::audioMuted = false;
RenderWindow* Game::window = NULL;
Font Game::generalFont;
Music Game::interfaceMusic;
Music Game::gameplayMusic;
SoundBuffer Game::buttonSFXBuffer;
Sound Game::buttonSFX;
SoundBuffer Game::impactSFXBuffer;
Sound Game::impactSFX;
float Game::deltaTime=0.0f;

Game::Game()
{
	window = new RenderWindow(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Cave Climber");

	gameStateInputActive = false;

	firstExecution = true;

	window->setFramerateLimit(60);

	clock.restart();
	deltaTime = 0.0f;

	menu = NULL;
	credits = NULL;
	gameplay = NULL;
	gameover = NULL;
	victory = NULL;

	generalFont.loadFromFile("fonts/londrina.otf");

	interfaceMusic.openFromFile("music/santi_song.ogg");
	interfaceMusic.setVolume(INTERFACE_MUSIC_INIT_VOLUME);
	interfaceMusic.setLoop(true);
	gameplayMusic.openFromFile("music/Friendly_Fire.ogg");
	gameplayMusic.setVolume(50);
	gameplayMusic.setLoop(true);

	buttonSFXBuffer.loadFromFile("sounds/button.ogg");
	buttonSFX.setBuffer(buttonSFXBuffer);
	impactSFXBuffer.loadFromFile("sounds/impact.ogg");;
	impactSFX.setBuffer(impactSFXBuffer);
}

Game::~Game()
{
	if (window) delete window;

	if (menu) delete menu;
	if (credits) delete credits;
	if (gameplay) delete gameplay;
	if (gameover) delete gameover;
	if (victory) delete victory;
}

void Game::updateMusic()
{
	if (!audioMuted)
	{
		if (gameplayMusic.getVolume() == 0)
		{
			gameplayMusic.setVolume(GAMEPLAY_MUSIC_INIT_VOLUME);
		}
			
		if (interfaceMusic.getVolume() == 0)
		{
			interfaceMusic.setVolume(INTERFACE_MUSIC_INIT_VOLUME);
		}
	}
	else
	{
		if (gameplayMusic.getVolume() != 0)
		{
			gameplayMusic.setVolume(0);
		}

		if (interfaceMusic.getVolume() != 0)
		{
			interfaceMusic.setVolume(0);
		}
	}
}

void Game::update()
{
	time = clock.restart();
	deltaTime = time.asSeconds();

	while (window->pollEvent(event))
	{
		if (event.type == Event::Closed)
		{
			window->close();
		}
	}

	switch (currentGameState)
	{
	case menu_state:
		if (gameover)
		{
			delete gameover;
			gameover = NULL;
		}
		if (victory)
		{
			delete victory;
			victory = NULL;
		}
		if (credits)
		{
			delete credits;
			credits = NULL;
		}
		if (gameplay)
		{
			delete gameplay;
			gameplay = NULL;
		}

		if (!menu) menu = new Menu();
		if (menu) menu->update();
		break;
	case credits_state:
		if (menu)
		{
			delete menu;
			menu = NULL;
		}

		if (!credits) credits = new Credits();
		if (credits) credits->update();
		break;
	case gameplay_state:
		if (menu)
		{
			delete menu;
			menu = NULL;
		}

		if (!gameplay) gameplay = new Gameplay(firstExecution);
		if (gameplay) gameplay->update();
		firstExecution = false;
		break;
	case gameOver_state:
		if (gameplay)
		{
			delete gameplay;
			gameplay = NULL;
		}

		if (!gameover) gameover = new GameOver();
		if (gameover) gameover->update();
		break;
	case victory_state:
		if (gameplay)
		{
			delete gameplay;
			gameplay = NULL;
		}

		if (!victory) victory = new Victory();
		if (victory) victory->update();
		break;
	default:
		break;
	}

	updateMusic();
}

void Game::draw()
{
	window->clear();

	switch (currentGameState)
	{
	case menu_state:
		if (menu) menu->draw();
		break;
	case credits_state:
		if (credits) credits->draw();
		break;
	case gameplay_state:
		if (gameplay) gameplay->draw();
		break;
	case gameOver_state:
		if (gameover) gameover->draw();
		break;
	case victory_state:
		if (victory) victory->draw();
		break;
	default:
		break;
	}

	window->display();
}

void Game::setGameStateInputActive(bool state)
{
	gameStateInputActive = state;
}

bool Game::getGameStateInputActive()
{
	return gameStateInputActive;
}

void Game::setAudioMuted(bool state)
{
	audioMuted = state;
}
bool Game::getAudioMuted()
{
	return audioMuted;
}

void Game::execute()
{
	while (window->isOpen())
	{
		update();
		draw();
	}
}
}