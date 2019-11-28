#include "game.h"

#include <SFML/Graphics.hpp>

#include "gameElements/player.h"

GameState Game::currentGameState = menu_state;
bool Game::gameStateInputActive = false;
RenderWindow* Game::window = NULL;
Font Game::generalFont;

Game::Game()
{
	window = new RenderWindow(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Platformer Game");
	if (window) window->setFramerateLimit(60);

	menu = NULL;
	gameplay = NULL;
	gameover = NULL;
	gameStateInputActive = false;

	generalFont.loadFromFile("assets/fonts/aescrawl.ttf");
}

Game::~Game()
{
	if (window) delete window;
	if (menu) delete menu;
	if (gameplay) delete gameplay;
	if (gameover) delete gameover;
}

void Game::update()
{
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

		if (!menu) menu = new Menu();
		if (menu) menu->update();
		break;
	case gameplay_state:
		if (menu)
		{
			delete menu;
			menu = NULL;
		}

		if (!gameplay) gameplay = new Gameplay();
		if (gameplay) gameplay->update();
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
	default:
		break;
	}
}

void Game::draw()
{
	window->clear();

	switch (currentGameState)
	{
	case menu_state:
		if (menu) menu->draw();
		break;
	case gameplay_state:
		if (gameplay) gameplay->draw();
		break;
	case gameOver_state:
		if (gameover) gameover->draw();
		break;
	default:
		break;
	}

	window->display();
}

void Game::execute()
{
	while (window->isOpen())
	{
		update();
		draw();
	}
}

void Game::changeGamestate(GameState newGamestate)
{
	currentGameState = newGamestate;
}

void Game::setGameStateInputActive(bool state)
{
	gameStateInputActive = state;
}

bool Game::getGameStateInputActive()
{
	return gameStateInputActive;
}