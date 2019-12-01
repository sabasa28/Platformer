#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <SFML/Audio.hpp>

#include "gameStates/menu.h"
#include "gameStates/credits.h"
#include "gameStates/gameplay.h"
#include "gameStates/gameover.h"
#include "gameStates/victory.h"

using namespace std;
using namespace sf;

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 600;

enum GameState
{
	menu_state,
	credits_state,
	gameplay_state,
	gameOver_state,
	victory_state
};

class Game
{

	Menu* menu;
	Credits* credits;
	Gameplay* gameplay;
	GameOver* gameover;
	Victory* victory;
	static bool gameStateInputActive;
	
	Event event;

	void update();
	void draw();

public:
	static GameState currentGameState;
	static RenderWindow* window;
	static Font generalFont;
	static Music interfaceMusic;
	static Music gameplayMusic;

	Game();
	~Game();
	void execute();
	static void setGameStateInputActive(bool state);
	static bool getGameStateInputActive();
};

#endif //GAME_H