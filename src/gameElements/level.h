#ifndef LEVEL_H
#define LEVEL_H

#include <SFML/Graphics.hpp>

using namespace sf;

class Platform
{
private:
	RectangleShape rectangle;
public:
	Platform();
	Platform(float x, float y, float width, float height, Color color);
	~Platform();
	RectangleShape getRec();
	int upperSide();
	int bottomSide();
	int leftSide();
	int rightSide();
	int centerX();
	int centerY();
};

#endif // !LEVEL_H

