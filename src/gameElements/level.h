#ifndef LEVEL_H
#define LEVEL_H

#include <SFML/Graphics.hpp>

#include <cmath>

using namespace sf;

enum NearestSide
{
	Top,
	Bottom,
	Right,
	Left
};

class Platform
{
private:
	RectangleShape rectangle;
public:
	Platform();
	Platform(float x, float y, float width, float height, Color color);
	~Platform();
	RectangleShape getRec();
	NearestSide checkProximity(RectangleShape rec, float collisionMargin);
	float getUpperSide();
	float getBottomSide();
	float getLeftSide();
	float getRightSide();
	float getCenterX();
	float getCenterY();
};

#endif //LEVEL_H

