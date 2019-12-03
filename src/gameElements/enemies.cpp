#include "enemies.h"

#include "general/game.h"

namespace game
{
Enemy::Enemy()
{
	alive = true;
	awake = false;
	rectangle.setSize({ static_cast<float>(ENEMY_SIZE), static_cast<float>(ENEMY_SIZE) });
	rectangle.setFillColor(Color::Red);
	rectangle.setPosition(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT - rectangle.getSize().y * 10);
	speed = { 0.0f, 0.0f };
	onGround = false;
}

Enemy::Enemy(Vector2f pos)
{
	alive = true;
	awake = false;
	rectangle.setSize({ 50, 50 });
	rectangle.setFillColor(Color::Red);
	rectangle.setPosition(pos.x, pos.y);
	speed = { 0.0f, 0.0f };
	onGround = false;
}

Enemy::~Enemy()
{
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

Vector2f Enemy::getCenter()
{
	return { getLeftSide() + rectangle.getSize().x / 2, getUpperSide() + rectangle.getSize().y / 2};
}

void Enemy::setAlive(bool newAlive)
{
	alive = newAlive;
}

bool Enemy::getAlive()
{
	return alive;
}

void Enemy::setAwake(bool newAwake)
{
	awake = newAwake;
}

bool Enemy::getAwake()
{
	return awake;
}

void Enemy::setOnGround(bool state)
{
	onGround = state;
}

bool Enemy::getOnGround()
{
	return onGround;
}

void Enemy::setSpeed(Vector2f newSpeed)
{
	speed = newSpeed;
}

Vector2f Enemy::getSpeed()
{
	return speed;
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
}