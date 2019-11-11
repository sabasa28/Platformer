#include "level.h"

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