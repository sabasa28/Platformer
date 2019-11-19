#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "gameElements/level.h"
#include "gameElements/player.h"
#include "gameElements/meleeEnemy.h"

class Gameplay
{
	Player* player;
	Platform* platform;
	Platform* platform2;
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
	void checkGameplayColls(Platform* plat);
};

#endif