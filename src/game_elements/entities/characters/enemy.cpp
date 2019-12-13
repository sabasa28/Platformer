#include "enemy.h"

#include "general/game.h"

namespace game
{
Enemy::Enemy()
{
	alive = true;
	awake = false;
	rectangle.setSize({ static_cast<float>(SIZE), static_cast<float>(SIZE) });
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

int Enemy::getSize()
{
	return SIZE;
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

void Enemy::updatePos(RectangleShape target)
{
	rectangle.setPosition(rectangle.getPosition() + speed/** Game::deltaTime*/);
	updateAwakeState(target);
	attack(target);


	if (onGround == false)
	{
		speed.y += GRAVITY;
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