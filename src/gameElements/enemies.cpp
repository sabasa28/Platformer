#include "enemies.h"
#include "general/game.h"

Enemy::Enemy()
{
	alive = true;
	awake = false;
	rectangle.setSize({ 50, 50 });
	rectangle.setFillColor(Color::Red);
	rectangle.setPosition(SCREEN_WIDTH / 1.3f, SCREEN_HEIGHT - rectangle.getSize().y);
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