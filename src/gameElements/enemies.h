#ifndef ENEMIES_H
#define ENEMIES_H

#include <SFML/Graphics.hpp>

#include "gameElements/level.h"

using namespace sf;

const int ENEMY_SIZE = 50;

class Enemy
{
private:
	bool alive;
	bool awake;
	const float gravity = 0.75f;
	RectangleShape rectangle;
	Vector2f speed;
	bool onGround;
public:
	Enemy();
	Enemy(Vector2f pos);
	~Enemy();
	bool getAlive();
	bool getAwake();
	RectangleShape getRec();
	void setRecX(float x);
	void setRecY(float y);
	Vector2f getSpeed();
	void setAlive(bool newAlive);
	void setAwake(bool newAwake);
	void setSpeed(Vector2f newSpeed);
	void updatePos(RectangleShape target);
	virtual void checkScreenLimits() = 0;
	bool getOnGround();
	void setOnGround(bool state);
	virtual void updateAwakeState(RectangleShape target) = 0;
	virtual void attack(RectangleShape target) = 0;
	float getUpperSide();
	float getBottomSide();
	float getLeftSide();
	float getRightSide();
};

#endif // !ENEMIES_H
