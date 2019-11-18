#include "enemies.h"
#include "general/game.h"

Enemy::Enemy()
{
	alive = true;
	awake = false;
	rectangle.setSize({ 50, 50 });
	rectangle.setFillColor(Color::Red);
	rectangle.setPosition(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT - rectangle.getSize().y *10 /*/ 3*/);
	speed = { 0.0f, 0.0f };
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

void Enemy::updatePos(RectangleShape target, RectangleShape platform)
{
	rectangle.setPosition(rectangle.getPosition()+speed);
	updateAwakeState(target);
	attack(target);
	if (!onGround(platform))
	{
		speed.y += gravity;
	}
	if (onGround(platform))
	{
		speed.y = 0;
		rectangle.setPosition(rectangle.getPosition().x,platform.getPosition().y-rectangle.getSize().y);
	}
	if (speed.y > MAXIMUM_SPEED)
	{
		speed.y = MAXIMUM_SPEED;
	}
}

bool Enemy::onGround(RectangleShape platform)
{
	if (platform.getGlobalBounds().top <= rectangle.getPosition().y+rectangle.getSize().y&&rectangle.getPosition().x<platform.getPosition().x+platform.getSize().x&& rectangle.getPosition().x + rectangle.getSize().x > platform.getPosition().x)
	{
		return true;
	}
	else
	{
		return false;
	}
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