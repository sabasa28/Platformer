#ifndef LEVEL_H
#define LEVEL_H

#include <SFML/Graphics.hpp>

using namespace sf;

const int PLATFORM_GRID_WIDTH = 50;
const int PLATFORM_GRID_HEIGHT = 50;
const int PLATFORM_SIZE = 100;
const int PLATFORM_MIN_Y_POS = 700;
const int PLATFORM_SPRITE_SIZE = 100;

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
	RectangleShape rectangle;
	RelativePlayerJumpState relativePlayerJumpsState;
	Texture texture;
	IntRect* textureRect;
	Sprite sprite;
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
	Sprite getSprite();
};

#endif //LEVEL_H

