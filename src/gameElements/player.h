#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>

#include "level.h"

using namespace sf;

const float MAXIMUM_SPEED = 20.0f;

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
	float jumpingSpeed = 25;
	float movingSpeed = 10;
	float gravity = 0.75f;
	Movement movement;

public:
	Player();
	~Player();
	void setRecPos(int x, int y);
	void setRecPos(Vector2f pos);
	void setRecX(int x);
	void setRecY(int y);
	void addToRecX(int x);
	void addToRecY(int y);
	void setSpeedX(int x);
	void setSpeedY(int y);
	float getSpeedX();
	float getSpeedY();
	Vector2f getSpeed();
	RectangleShape getRec();
	JumpState getJumpState();
	float getJumpingSpeed();
	void checkKeyPressedInput(Event event);
	void checkKeyDownInput(Event event, RenderWindow* &window);
	void checkKeyReleasedInput(Event event);
	void setMoveRight(bool state);
	void setMoveLeft(bool state);
	void jump();
	void setJumpState(JumpState state);
	void updateMovement();
	void updatePosition();
	void checkScreenLimits();
	bool colliding(RectangleShape rectangle);
	bool fallingOffPlatform(Platform* platform);
	int getUpperSide();
	int getBottomSide();
	int getLeftSide();
	int getRightSide();
};

#endif //PLAYER_H
