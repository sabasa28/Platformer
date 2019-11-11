#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>

#include "gameElements/level.h"

using namespace sf;

const float MAXIMUM_SPEED = 20.0f;
const float GRAVITY_INITIAL_VALUE = 0.75f;

struct Movement
{
	bool right;
	bool left;
};

extern enum JumpState
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
	float jumpingSpeed = 20;
	float movingSpeed = 10;
	float gravity = GRAVITY_INITIAL_VALUE;
	Movement movement;

public:
	Player();
	~Player();
	void setRecPos(int x, int y);
	void setRecX(int x);
	void setRecY(int y);
	void addToRecX(int x);
	void addToRecY(int y);
	RectangleShape getRec();
	JumpState getJumpState();
	void checkKeyPressedInput(Event event);
	void checkKeyDownInput(Event event, RenderWindow &window);
	void checkKeyReleasedInput(Event event);
	void setMoveRight(bool state);
	void setMoveLeft(bool state);
	void jump();
	void setJumpState(JumpState state);
	void updateMovement();
	void checkScreenLimits();
	bool onPlatform(Platform* platform);
	bool collidingWithPlatformFromBelow(Platform* platform);
	bool collidingWithPlatformFromLeft(Platform* platform);
	bool collidingWithPlatformFromRight(Platform* platform);
	bool fallingOffPlatform(Platform* platform);
	int upperSide();
	int bottomSide();
	int leftSide();
	int rightSide();
};

#endif //PLAYER_H
