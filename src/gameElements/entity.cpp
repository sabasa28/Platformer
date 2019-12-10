#include "entity.h"

namespace game
{
Entity::Entity(RectangleShape rec, Texture tex, IntRect* texRec, Sprite spr)
{
	rectangle = rec;
	texture = tex;
	textureRect = texRec;
	sprite = spr;
}

Entity::~Entity()
{
}

void Entity::setRecPosition(float x, float y)
{
	rectangle.setPosition(x, y);
}

void Entity::setRecPosition(Vector2f pos)
{
	rectangle.setPosition(pos.x, pos.y);
}

void Entity::setRecPositionX(float x)
{
	rectangle.setPosition(x, rectangle.getPosition().y);
}

void Entity::setRecPositionY(float y)
{
	rectangle.setPosition(rectangle.getPosition().x, y);
}

Vector2f Entity::getPosition()
{
	rectangle.getPosition();
}

float Entity::getPositionX()
{
	rectangle.getPosition().x;
}

float Entity::getPositionY()
{
	rectangle.getPosition().y;
}

float Entity::getUpperSide()
{
	return rectangle.getPosition().y;
}

float Entity::getBottomSide()
{
	return getUpperSide() + rectangle.getSize().y;
}

float Entity::getLeftSide()
{
	return rectangle.getPosition().x;
}

float Entity::getRightSide()
{
	return getLeftSide() + rectangle.getSize().x;
}

float Entity::getCenterX()
{
	return getLeftSide() + rectangle.getSize().x / 2;
}

float Entity::getCenterY()
{
	return getUpperSide() + rectangle.getSize().y / 2;
}

Sprite Entity::getSprite()
{
	return sprite;
}

void Entity::addToPosition(float x, float y)
{
	rectangle.setPosition(rectangle.getPosition().x + x, rectangle.getPosition().y + y);
}

void Entity::addToPosition(Vector2f pos)
{
	rectangle.setPosition(rectangle.getPosition().x + pos.x, rectangle.getPosition().y + pos.y);
}

void Entity::addToPositionX(float x)
{
	rectangle.setPosition(rectangle.getPosition().x + x, rectangle.getPosition().y);
}

void Entity::addToPositionY(float y)
{
	rectangle.setPosition(rectangle.getPosition().x, y);
}
}