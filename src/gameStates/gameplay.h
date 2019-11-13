#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "gameElements/level.h"
#include "gameElements/player.h"

class Gameplay
{
	Player* player;
	Platform* platform;

public:
	Gameplay();
	~Gameplay();
	void init();
	void update(RenderWindow* &window);
	void draw(RenderWindow* &window);
	void close();
	float getCollisionMargin(float jumpingSpeed);
	void checkGameplayColls(Platform* plat);
};

#endif