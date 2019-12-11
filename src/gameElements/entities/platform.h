#ifndef PLATFORM_H
#define PLATFORM_H

#include <SFML/Graphics.hpp>

#include "gameElements/entity.h"

using namespace sf;

namespace game
{
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

class Platform : public Entity
{
	const int SIZE = 100;
	const int MIN_Y_POS = 700;
	const int SPRITE_SIZE = 100;

	RelativePlayerJumpState relativePlayerJumpsState;
	Texture texture;
	IntRect* textureRect;
	Sprite sprite;

public:
	Platform(int x, int y);
	~Platform();
	int getSize();
	void draw();
	NearestSide checkSideProximity(RectangleShape rec, float collisionMargin);
	void setRelativePlayerJumpState(RelativePlayerJumpState jumpState);
	RelativePlayerJumpState getRelativePlayerJumpState();
	Sprite getSprite();
};
}

#endif //PLATFORM_H

