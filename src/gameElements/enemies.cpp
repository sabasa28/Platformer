#include "enemies.h"

#include "general/game.h"

Enemy::Enemy()
{
	alive = true;
	awake = false;
	rectangle.setSize({ 50, 50 });
	rectangle.setFillColor(Color::Red);
	rectangle.setPosition(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT - rectangle.getSize().y *10);
	speed = { 0.0f, 0.0f };
	onGround = false;
}

Enemy::~Enemy()
{
}

bool Enemy::getAlive()
{
	return alive;
}

bool Enemy::getAwake()
{
	return awake;
}

RectangleShape Enemy::getRec() 
{
	return rectangle;
}

void Enemy::setRecX(float x)
{
	rectangle.setPosition(x, rectangle.getPosition().y);
}

void Enemy::setRecY(float y)
{
	rectangle.setPosition(rectangle.getPosition().x, y);
}

Vector2f Enemy::getSpeed()
{
	return speed;
}

void Enemy::setAlive(bool newAlive)
{
	alive = newAlive;
}

void Enemy::setAwake(bool newAwake)
{
	awake = newAwake;
}

void Enemy::setSpeed(Vector2f newSpeed)
{
	speed = newSpeed;
}

void Enemy::updatePos(RectangleShape target)
{
	rectangle.setPosition(rectangle.getPosition() + speed);
	updateAwakeState(target);
	attack(target);


	if (onGround == false)
	{
		speed.y += gravity;
	}
	else
	{
		speed.y = 0;
	}

	if (speed.y > MAXIMUM_SPEED)
	{
		speed.y = MAXIMUM_SPEED;
	}
}

bool Enemy::getOnGround()
{
	return onGround;
}

void Enemy::setOnGround(bool state)
{
	onGround= state;
}

float Enemy::getUpperSide()
{
	return rectangle.getPosition().y;
}

float Enemy::getBottomSide()
{
	return getUpperSide() + rectangle.getSize().y;
}

float Enemy::getLeftSide()
{
	return rectangle.getPosition().x;
}

float Enemy::getRightSide()
{
	return getLeftSide() + rectangle.getSize().x;
}