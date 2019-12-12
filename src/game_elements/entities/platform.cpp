#include "platform.h"
#include <iostream>
namespace game
{
NearestSide nearestSide;

float disToTop;
float disToBottom;
float disToLeft;
float disToRight;
float lowestDistance;

Platform::Platform(int x, int y)
{
	rectangle.setSize({ static_cast<float>(SIZE), static_cast<float>(SIZE) });
	rectangle.setPosition({ static_cast<float>(SIZE) * x, MIN_Y_POS - static_cast<float>(SIZE) * y });
	relativePlayerJumpsState = falling_relative;
	texture.loadFromFile("images/dirt.png");
	textureRect = new IntRect(0, 0, SPRITE_SIZE, SPRITE_SIZE);
	sprite.setTexture(texture);
	sprite.setTextureRect(*textureRect);
	sprite.setPosition(getRec().getPosition().x, getRec().getPosition().y);
}

Platform::~Platform()
{
}

int Platform::getSize()
{
	return SIZE;
}

void Platform::draw()
{

}

NearestSide Platform::checkSideProximity(RectangleShape rec, float collisionMargin, bool verticalPriorizatrion)
{
	disToTop = abs((rec.getPosition().y + rec.getSize().y) - rectangle.getPosition().y);
	disToBottom = abs(rec.getPosition().y - (rectangle.getPosition().y + rectangle.getSize().y));
	disToLeft = abs((rec.getPosition().x + rec.getSize().x) - rectangle.getPosition().x);
	disToRight = abs(rec.getPosition().x - (rectangle.getPosition().x + rectangle.getSize().x));

	if (!verticalPriorizatrion) 
	{
		if (disToTop < disToBottom)
		{
			lowestDistance = disToTop;
			nearestSide = Top;
		}
		else
		{
			lowestDistance = disToBottom;
			nearestSide = Bottom;
		}
		if (disToRight - collisionMargin < lowestDistance)
		{
			lowestDistance = disToRight;
			nearestSide = Right;
		}
		if (disToLeft - collisionMargin < lowestDistance)
		{
			nearestSide = Left;
		}
	}
	else
	{
		if (disToTop < disToBottom )
		{
			lowestDistance = disToTop - collisionMargin;
			nearestSide = Top;
		}
		else
		{
			lowestDistance = disToBottom;
			nearestSide = Bottom;
		}
		if (disToRight  < lowestDistance)
		{
			lowestDistance = disToRight;
			nearestSide = Right;
		}
		if (disToLeft  < lowestDistance)
		{
			nearestSide = Left;
		}
	}

	return nearestSide;
}

void Platform::setRelativePlayerJumpState(RelativePlayerJumpState jumpState)
{
	relativePlayerJumpsState = jumpState;
}

RelativePlayerJumpState Platform::getRelativePlayerJumpState()
{
	return relativePlayerJumpsState;
}

Sprite Platform::getSprite()
{
	return sprite;
}
}