#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include <SFML/Audio.hpp>

#include "gameElements/level.h"
#include "gameElements/player.h"
#include "gameElements/meleeEnemy.h"
#include "uiElements/displayText.h"

const int PAUSE_TEXT_Y = 75;
const int ENEMY_AMMOUNT = 3;
const int BACKGROUND_SPRITE_SIZE = 100;
const int GOAL_SIZE = 50;
const int GOAL_SPRITE_SIZE = GOAL_SIZE;

class Gameplay
{
	bool pause;
	bool pauseButtonPressed;
	Platform* platformGrid[PLATFORM_GRID_HEIGHT][PLATFORM_GRID_WIDTH];
	Player* player;
	MeleeEnemy* meleeEnemy[ENEMY_AMMOUNT];
	RectangleShape* goal;
	View* camera;
	Texture backgroundTexture;
	IntRect* backgroundTextureRect;
	Sprite backgroundSprite;
	Texture goalTexture;
	IntRect* goalTextureRect;
	Sprite goalSprite;

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
	void setPause(bool state);
	bool getPause();
	void update();
	void draw();
	float getCollisionMargin(float jumpingSpeed);
	void checkGameplayColls(Platform* plat[][PLATFORM_GRID_WIDTH]);
	void drawBackground(int x, int y);
};

#endif //GAMEPLAY_H