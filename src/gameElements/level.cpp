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

int Platform::bottomSide()
{
	return rectangle.getPosition().y + rectangle.getSize().y;
}

int Platform::upperSide()
{
	return rectangle.getPosition().y;
}

int Platform::rightSide()
{
	return rectangle.getPosition().x + rectangle.getSize().x;
}

int Platform::leftSide()
{
	return rectangle.getPosition().x;
}