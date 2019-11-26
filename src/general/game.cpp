#include "game.h"

#include <SFML/Graphics.hpp>

#include "gameElements/player.h"
#include "gameElements/level.h"


GameState Game::currentGameState = menu_state;

Game::Game()
{
	/////TEST


	//text.setFillColor(Color::Red);
	//text.setCharacterSize(200);
	//text.setStyle(Text::Bold);
	//text.setString("GAME OVER");
	//text.setPosition(200,200);
	//text.setFont();
	rect.setSize({ 200, 200 });
	rect.setPosition(200, 200);
	rect.setFillColor(Color::Red);

	/////TEST

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
	menu = new Menu();
	gameplay = new Gameplay();
	gameover = new GameOver();
	window = new RenderWindow(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Platformer Game");

	if(menu)menu->init();
	if(gameplay)gameplay->init(window);
	
	if(window)window->setFramerateLimit(60);
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
		if(menu) menu->update(window);
		break;
	case gameplay_state:
		if(gameplay)gameplay->update(window);
		break;
	case gameOver_state:/*
		cout << "GAME OVER"<<endl;
		if (Keyboard::isKeyPressed(Keyboard::Enter))
		{
			currentGameState = gameplay_state;
		}*/
		if (gameplay) delete gameplay;
		gameplay = NULL;
		gameplay = new Gameplay();
		gameplay->init(window);
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
		if(menu)menu->draw(window);
		break;
	case gameplay_state:
		if(gameplay)gameplay->draw(window);
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
	init();
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