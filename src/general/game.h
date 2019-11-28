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

	Menu* menu;
	Gameplay* gameplay;
	GameOver* gameover;
	static bool gameStateInputActive;
	
	Event event;

	void update();
	void draw();

public:
	static RenderWindow* window;
	static Font generalFont;

	Game();
	~Game();
	void execute();
	static void changeGamestate(GameState newGamestate);
	static void setGameStateInputActive(bool state);
	static bool getGameStateInputActive();
};


#endif //GAME_H