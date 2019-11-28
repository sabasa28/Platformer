#include "game.h"

#include <SFML/Graphics.hpp>

#include "gameElements/player.h"

GameState Game::currentGameState = menu_state;
RenderWindow* Game::window = NULL;
Font generalFont;

Game::Game()
{
	window = new RenderWindow(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Platformer Game");
	if (window) window->setFramerateLimit(60);

	menu = NULL;
	gameplay = NULL;
	gameover = NULL;

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
		if (menu == NULL) menu = new Menu();
		if (menu) menu->update();
		break;
	case gameplay_state:
		if (gameplay == NULL) gameplay = new Gameplay();
		if (gameplay) gameplay->update();
		break;
	case gameOver_state:
		if (gameplay) delete gameplay;
		gameplay = NULL;
		gameplay = new Gameplay();
		Game::changeGamestate(gameplay_state);
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
		if(menu)menu->draw();
		break;
	case gameplay_state:
		if(gameplay)gameplay->draw();
		break;
	case gameOver_state:/*
		window->clear();
		window->draw(rect);
		window->display();*/
		break;
	default:
		break;
	}
}

void Game::execute()
{
	//init();
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