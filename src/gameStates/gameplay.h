#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "gameElements/level.h"
#include "gameElements/player.h"
#include "gameElements/meleeEnemy.h"

const int ENEMY_AMMOUNT = 3;

class Gameplay
{
	Platform* platformGrid[PLATFORM_GRID_HEIGHT][PLATFORM_GRID_WIDTH];
	Player* player;
	MeleeEnemy* meleeEnemy[ENEMY_AMMOUNT];
	RectangleShape* goal;
	View* camera;

public:
	Gameplay();
	~Gameplay();
	void update();
	void draw();
	float getCollisionMargin(float jumpingSpeed);
	void checkGameplayColls();
	void checkGameplayColls2(Platform* plat);
};

#endif //GAMEPLAY_H