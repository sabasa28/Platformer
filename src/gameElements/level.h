#ifndef LEVEL_H
#define LEVEL_H

#include <SFML/Graphics.hpp>

using namespace sf;

const int PLATFORM_GRID_WIDTH = 50;
const int PLATFORM_GRID_HEIGHT = 50;
const int PLATFORM_SIZE = 100;
const int PLATFORM_MIN_Y_POS = 700;

enum NearestSide
{
	Top,
	Bottom,
	Right,
	Left
};

enum RelativePlayerJumpState
{
	onGround_relative,
	falling_relative
};

class Platform
{
private:
	RectangleShape rectangle;
	RelativePlayerJumpState relativePlayerJumpsState;
public:
	Platform(int x, int y);
	~Platform();
	RectangleShape getRec();
	NearestSide checkSideProximity(RectangleShape rec, float collisionMargin);
	void setRelativePlayerJumpState(RelativePlayerJumpState jumpState);
	RelativePlayerJumpState getRelativePlayerJumpState();
	float getUpperSide();
	float getBottomSide();
	float getLeftSide();
	float getRightSide();
	float getCenterX();
	float getCenterY();
};

#endif //LEVEL_H

