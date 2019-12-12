#include "character.h"

namespace game
{
Character::Character()
{
	speed = { 1, 1 };
}

Character::Character(float speX, float speY, RectangleShape rec, Texture tex, IntRect* texRec, Sprite spr) : Entity(rec, tex, texRec, spr)
{
	speed = { speX, speY };
}

Character::Character(Vector2f spe, RectangleShape rec, Texture tex, IntRect* texRec, Sprite spr) : Entity(rec, tex, texRec, spr)
{
	speed = spe;
}

Character::~Character()
{
}

void Character::setSpeed(float x, float y)
{
	speed = { x, y };
}

void Character::setSpeed(Vector2f spe)
{
	speed = { spe.x, spe.y };
}

void Character::setSpeedX(float x)
{
	speed.x = x;
}

void Character::setSpeedY(float y)
{
	speed.y = y;
}

Vector2f Character::getSpeed()
{
	return speed;
}

float Character::getSpeedX()
{
	return speed.x;
}

float Character::getSpeedY()
{
	return speed.y;
}
}