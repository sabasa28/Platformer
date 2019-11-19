#include "level.h"

#include <cmath>

NearestSide nearestSide;

float disToTop;
float disToBottom;
float disToLeft;
float disToRight;
float lowestDistance;

Platform::Platform()
{
	rectangle.setSize({ 200, 30 });
	rectangle.setPosition({ 100, 100 });
	rectangle.setFillColor(Color::White);
}

Platform::Platform(float x, float y, float width, float height, Color color)
{
	rectangle.setSize({ width,height });
	rectangle.setPosition({ x, y });
	rectangle.setFillColor(color);
}

Platform::~Platform()
{
}

RectangleShape Platform::getRec()
{
	return rectangle;
}

NearestSide Platform::checkSideProximity(RectangleShape rec, float collisionMargin)
{
	disToTop = abs((rec.getPosition().y + rec.getSize().y) - rectangle.getPosition().y);
	disToBottom = abs(rec.getPosition().y - (rectangle.getPosition().y + rectangle.getSize().y));
	disToLeft = abs((rec.getPosition().x + rec.getSize().x) - rectangle.getPosition().x);
	disToRight = abs(rec.getPosition().x - (rectangle.getPosition().x + rectangle.getSize().x));

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

	return nearestSide;
}

float Platform::getUpperSide()
{
	return rectangle.getPosition().y;
}

float Platform::getBottomSide()
{
	return getUpperSide() + rectangle.getSize().y;
}

float Platform::getLeftSide()
{
	return rectangle.getPosition().x;
}

float Platform::getRightSide()
{
	return getLeftSide() + rectangle.getSize().x;
}

float Platform::getCenterX()
{
	return getLeftSide() + rectangle.getSize().x / 2;
}

float Platform::getCenterY()
{
	return getUpperSide() + rectangle.getSize().y / 2;
}