#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include <SFML/Audio.hpp>

#include "game_elements/entities/platform.h"
#include "game_elements/entities/gold_coin.h"
#include "game_elements/entities/characters/player.h"
#include "game_elements/entities/characters/enemies/slime_block.h"
#include "game_elements/entities/pause.h"
#include "game_elements/entities/controls.h"

namespace game
{

const int GRID_HEIGHT = 50;
const int GRID_WIDTH = 130;
const int ENEMY_AMMOUNT = 4;

class Gameplay
{
	const int BACKGROUND_SPRITE_SIZE = 100;
	const int GOAL_SIZE = 50;
	const int GOAL_SPRITE_SIZE = GOAL_SIZE;
	const float FALL_LIMIT = -1000.0f;
	const float BACKGROUND_TILE_SIZE = 100.0f;
	const float BACKGROUND_MIN_POS = 700.0f;
	bool pauseButtonPressed;
	bool muteButtonPressed;
	bool controlsButtonPressed;
	bool showControls;
	Platform* platformGrid[GRID_HEIGHT][GRID_WIDTH];
	Player* player;
	SlimeBlock* slimeBlock[ENEMY_AMMOUNT];
	GoldCoin* goldCoin;
	bool paused;
	View* camera;
	Pause* pause;
	Controls* controls;
	Texture backgroundTexture;
	IntRect* backgroundTextureRect;
	Sprite backgroundSprite;

public:
	static SoundBuffer footstepSFXBuffer;
	static Sound footstepSFX;
	static SoundBuffer jumpSFXBuffer;
	static Sound jumpSFX;
	static SoundBuffer coinsSFXBuffer;
	static Sound coinsSFX;

	Gameplay(bool firstExecution);
	~Gameplay();
	void checkKeyDownInput();
	void checkGameplayColls(Platform* plat[][GRID_WIDTH]);
	void setPause(bool state);
	bool getPause();
	void update();
	void drawBackground(int x, int y);
	void draw();
};
}

#endif //GAMEPLAY_H