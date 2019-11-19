#ifndef ENEMIES_H
#define ENEMIES_H

#include <SFML/Graphics.hpp>

using namespace sf;

class Enemy
{
private:
	bool alive;
	bool awake;
	const float gravity = 0.75f;
	RectangleShape rectangle;
	Vector2f speed;
public:
	Enemy();
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
	void updatePos(RectangleShape target, RectangleShape platform);
	virtual void checkScreenLimits() = 0;
	bool onGround(RectangleShape platform);
	virtual void updateAwakeState(RectangleShape target) = 0;
	virtual void attack(RectangleShape target) = 0;
	float getUpperSide();
	float getBottomSide();
	float getLeftSide();
	float getRightSide();
};

#endif // !ENEMIES_H
