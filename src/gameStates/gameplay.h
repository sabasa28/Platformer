#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "gameElements/level.h"
#include "gameElements/player.h"
#include "gameElements/meleeEnemy.h"

const int PLATFORMS_WIDTH = 10;
const int PLATFORMS_HEIGHT = 6;
const int PLATFORM_SIZE = 100;

class Gameplay
{
	Player* player;
	JumpState jumpstatePlatform[PLATFORMS_WIDTH][PLATFORMS_HEIGHT];
	Platform* platforms[PLATFORMS_WIDTH][PLATFORMS_HEIGHT];
	MeleeEnemy* meleeEnemy;
	View* camera;

public:
	Gameplay();
	~Gameplay();
	void init(RenderWindow* &window);
	void update(RenderWindow* &window);
	void draw(RenderWindow* &window);
	void close();
	float getCollisionMargin(float jumpingSpeed);
	void checkGameplayColls(Platform* plat, int x, int y);
	void checkGameplayColls2(Platform* plat);
};

#endif