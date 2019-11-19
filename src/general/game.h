#ifndef GAME_H
#define GAME_H

#include <iostream>
#include "gameStates/menu.h"
#include "gameStates/gameplay.h"
#include "gameStates/gameover.h"

using namespace std;
using namespace sf;

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 600;

enum GameState
{
	menu_state,
	gameplay_state,
	gameOver_state
};

class Game
{
	static GameState currentGameState;

	Text text;//TEST
	RectangleShape rect;


	RenderWindow* window;
	
	Menu* menu;
	Gameplay* gameplay;
	GameOver* gameover;
	
	Event event;
	
	void init();
	void update();
	void draw();
	void close();

public:
	Game();
	~Game();
	void execute();
	static void changeGamestate(GameState newGamestate);
};


#endif //GAME_H