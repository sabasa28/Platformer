#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>

#include "level.h"

using namespace sf;

const  float MAXIMUM_SPEED = 20.0f;

struct Movement
{
	bool right;
	bool left;
};

enum JumpState
{
	onGround,
	start,
	ascending,
	falling
};

class Player
{
private:
	RectangleShape rectangle;
	Vector2f speed;
	bool jumping;
	JumpState jumpState;
	float jumpingSpeed = 25;
	float movingSpeed = 10;
	float gravity = 0.75f;
	Movement movement;

public:
	Player();
	~Player();
	void setRecPos(float x, float y);
	void setRecPos(Vector2f pos);
	void setRecX(float x);
	void setRecY(float y);
	void addToRecX(float x);
	void addToRecY(float y);
	void setSpeedX(float x);
	void setSpeedY(float y);
	float getSpeedX();
	float getSpeedY();
	Vector2f getSpeed();
	RectangleShape getRec();
	JumpState getJumpState();
	float getJumpingSpeed();
	void checkKeyPressedInput();
	void checkKeyDownInput();
	void checkKeyReleasedInput();
	void setMoveRight(bool state);
	void setMoveLeft(bool state);
	void jump();
	void setJumpState(JumpState state);
	void updateMovement();
	void updatePosition();
	void checkScreenLimits();
	bool colliding(RectangleShape rec);
	bool fallingOffPlatform(Platform* platform);
	float getUpperSide();
	float getBottomSide();
	float getLeftSide();
	float getRightSide();
	float getCenterX();
	float getCenterY();
};

#endif //PLAYER_H
