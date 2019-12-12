#ifndef ENEMY_H
#define ENEMY_H

#include "game_elements/entities/character.h"
#include "game_elements/entities/platform.h"

using namespace sf;

namespace game
{
class Enemy : public Character
{
protected:
	const int SIZE = 50;
	const float MAXIMUM_SPEED = 20.0f;

	bool alive;
	bool awake;
	bool onGround;

public:
	Enemy();
	Enemy(Vector2f pos);
	~Enemy();
	int getSize();
	void setAlive(bool newAlive);
	bool getAlive();
	void setAwake(bool newAwake);
	bool getAwake();
	void setOnGround(bool state);
	bool getOnGround();
	virtual void updateAwakeState(RectangleShape target) = 0;
	virtual void attack(RectangleShape target) = 0;
	void updatePos(RectangleShape target);
};
}

#endif // !ENEMY_H
