#include "game.h"

#include <SFML/Graphics.hpp>

#include "gameElements/player.h"
#include "gameElements/level.h"



Game::Game()
{
	currentGameState = menu_state;
	
	gameplay = NULL;
	gameover = NULL;
	menu = NULL;
	window = NULL;
}

Game::~Game()
{
	if (window) delete window;
	if (gameplay) delete gameplay;
	if (gameover) delete gameover;
}

void Game::init()
{
	currentGameState = gameplay_state;

	gameplay = new Gameplay();
	gameover = new GameOver();
	menu = new Menu();
	window = new RenderWindow(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Platformer Game");

	gameplay->init();

	window->setFramerateLimit(60);
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
		break;
	case gameplay_state:
		gameplay->update(window, event);
		break;
	case gameOver_state:
		break;
	default:
		break;
	}

}

void Game::draw()
{

	switch (currentGameState)
	{
	case menu_state:
		break;
	case gameplay_state:
		gameplay->draw(window);
		break;
	case gameOver_state:
		break;
	default:
		break;
	}
}

void Game::close()
{

}

void Game::execute()
{
	init();
	while (window->isOpen())
	{
		update();
		draw();
	}
	close();
}