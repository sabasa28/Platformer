#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>

#include "level.h"

using namespace sf;

const int PLAYER_WIDTH = 50;
const int PLAYER_HEIGHT = 80;
const int PLAYER_SPRITE_SIZE = 128;
const int PLAYER_SPRITE_Y_SETOFF = 30;
const  float MAXIMUM_SPEED = 20.0f;

struct Movement
{
	bool right;
	bool left;
};

enum Action
{
	standing_action,
	walking_action,
	jumping_action
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
	RectangleShape rectangle;
	Movement movement;
	bool facingRight;
	Vector2f speed;
	float movingSpeed = 10.0f;
	bool jumping;
	JumpState jumpState;
	float jumpingSpeed = 20.0f;
	float gravity = 0.75f;
	Texture texture;
	IntRect* textureRect;
	Sprite sprite;
	Clock clock;
	Time timer;
	Action currentAction;
	Action lastFrameAction;

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
	RectangleShape getRec();
	Sprite getSprite();
	void setCurrentAction(Action action);
	Action getCurrentAction();
	void setLastFrameAction(Action action);
	Action getLastFrameAction();
	Vector2f getSpeed();
	JumpState getJumpState();
	float getJumpingSpeed();
	void checkKeyPressedInput();
	void checkKeyDownInput();
	void checkKeyReleasedInput();
	void setMoveRight(bool state);
	void setMoveLeft(bool state);
	void setFacingRight(bool state);
	bool getFacingRight();
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
	void updateSprite();
};

#endif //PLAYER_H
