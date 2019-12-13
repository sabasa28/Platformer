#ifndef GAME_H
#define GAME_H

#include <iostream>

#include <SFML/Audio.hpp>

#include "game_states/gameplay.h"
#include "game_states/screens/menu.h"
#include "game_states/screens/credits.h"
#include "game_states/screens/game_over.h"
#include "game_states/screens/victory.h"

using namespace std;
using namespace sf;

namespace game
{
const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 600;
const int PARAGRAPH_FONT_SIZE = 30;
const int INTERFACE_MUSIC_INIT_VOLUME = 100;
const int GAMEPLAY_MUSIC_INIT_VOLUME = 50;

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
	static bool gameStateInputActive;
	static bool audioMuted;
	bool firstExecution;
	Clock clock;
	Time time;


	Menu* menu;
	Credits* credits;
	Gameplay* gameplay;
	GameOver* gameover;
	Victory* victory;

	void updateMusic();
	void update();
	void draw();

public:
	static float deltaTime;
	static Event event;
	static GameState currentGameState;
	static RenderWindow* window;
	static Font generalFont;
	static Music interfaceMusic;
	static Music gameplayMusic;
	static SoundBuffer buttonSFXBuffer;
	static Sound buttonSFX;
	static SoundBuffer impactSFXBuffer;
	static Sound impactSFX;

	Game();
	~Game();
	static void setGameStateInputActive(bool state);
	static bool getGameStateInputActive();
	static void setAudioMuted(bool state);
	static bool getAudioMuted();
	void execute();
};
}

#endif //GAME_H