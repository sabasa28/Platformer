#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include <SFML/Audio.hpp>

#include "game_elements/entities/platform.h"
#include "game_elements/entities/gold_coin.h"
#include "game_elements/entities/characters/player.h"
#include "game_elements/entities/characters/enemies/slime_block.h"
#include "game_elements/entities/display_text.h"

namespace game
{
const int ENEMY_AMMOUNT = 4;

const int BACKGROUND_SPRITE_SIZE = 100;

const int GOAL_SIZE = 50;
const int GOAL_SPRITE_SIZE = GOAL_SIZE;

const int PAUSE_TEXT_AMMOUNT = 4;
const int PAUSE_TEXT_Y = 100;
const int PAUSE_FONT_SIZE = 30;
const int PAUSE_SPACE_BETWEEN_TEXT = 20;
const Vector2f PAUSE_POS = { 250.0f, 100.0f };
const Vector2f PAUSE_SIZE = { 400.0f, 200.0f };
const int GRID_WIDTH = 100;
const int GRID_HEIGHT = 50;

class Gameplay
{
	bool pauseButtonPressed;
	bool muteButtonPressed;
	Platform* platformGrid[GRID_HEIGHT][GRID_WIDTH];
	Player* player;
	SlimeBlock* slimeBlock[ENEMY_AMMOUNT];
	GoldCoin* goldCoin;
	bool paused;
	RectangleShape pauseRec;
	DisplayText* pauseTexts[PAUSE_TEXT_AMMOUNT];
	View* camera;
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

	Gameplay();
	~Gameplay();
	void checkKeyDownInput();
	void checkGameplayColls(Platform* plat[][GRID_WIDTH]);
	void setPause(bool state);
	bool getPause();
	void centerPause();
	void update();
	void drawBackground(int x, int y);
	void draw();
};
}

#endif //GAMEPLAY_H