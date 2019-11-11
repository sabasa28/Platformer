#include "level.h"

NearestSide side;

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

NearestSide Platform::checkProximity(RectangleShape rec, float collisionMargin)
{
	disToTop = abs((rec.getPosition().y + rec.getSize().y) - rectangle.getPosition().y);
	disToBottom = abs(rec.getPosition().y - (rectangle.getPosition().y + rectangle.getSize().y));
	disToLeft = abs((rec.getPosition().x + rec.getSize().x) - rectangle.getPosition().x);
	disToRight = abs(rec.getPosition().x - (rectangle.getPosition().x + rectangle.getSize().x));

	if (disToTop < disToBottom)
	{
		lowestDistance = disToTop;
		side = Top;
	}
	else
	{
		lowestDistance = disToBottom;
		side = Bottom;
	}
	if (disToRight - collisionMargin < lowestDistance)
	{
		lowestDistance = disToRight;
		side = Right;
	}
	if (disToLeft - collisionMargin < lowestDistance)
	{
		side = Left;
	}

	return side;
}

int Platform::upperSide()
{
	return rectangle.getPosition().y;
}

int Platform::bottomSide()
{
	return upperSide() + rectangle.getSize().y;
}

int Platform::leftSide()
{
	return rectangle.getPosition().x;
}

int Platform::rightSide()
{
	return leftSide() + rectangle.getSize().x;
}

int Platform::centerX()
{
	return upperSide() + rectangle.getSize().y / 2;
}

int Platform::centerY()
{
	return leftSide() + rectangle.getSize().x / 2;
}