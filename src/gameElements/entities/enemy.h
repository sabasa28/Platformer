#ifndef ENEMY_H
#define ENEMY_H

#include "character.h"
#include "platform.h"

using namespace sf;

namespace game
{
const int ENEMY_SIZE = 50;

class Enemy : public Character
{
	//RectangleShape rectangle;
	bool alive;
	bool awake;
	bool onGround;
	/*Vector2f speed;
	const float gravity = 0.75f;*/

public:
	Enemy();
	Enemy(Vector2f pos);
	~Enemy();
	/*RectangleShape getRec();
	void setRecX(float x);
	void setRecY(float y);
	float getUpperSide();
	float getBottomSide();
	float getLeftSide();
	float getRightSide();
	Vector2f getCenter();*/
	void setAlive(bool newAlive);
	bool getAlive();
	void setAwake(bool newAwake);
	bool getAwake();
	void setOnGround(bool state);
	bool getOnGround();
	/*void setSpeed(Vector2f newSpeed);
	Vector2f getSpeed();*/
	virtual void updateAwakeState(RectangleShape target) = 0;
	virtual void attack(RectangleShape target) = 0;
	void updatePos(RectangleShape target);
};
}

#endif // !ENEMY_H
