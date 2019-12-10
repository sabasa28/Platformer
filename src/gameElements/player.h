#ifndef PLAYER_H
#define PLAYER_H

//#include "level.h"

using namespace sf;

namespace game
{
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
	RectangleShape getRec();
	void setRecPos(float x, float y);
	void setRecPos(Vector2f pos);
	void setRecX(float x);
	void addToRecX(float x);
	void setRecY(float y);
	void addToRecY(float y);
	float getUpperSide();
	float getBottomSide();
	float getLeftSide();
	float getRightSide();
	float getCenterX();
	float getCenterY();
	void setMoveRight(bool state);
	void setMoveLeft(bool state);
	Vector2f getSpeed();
	void setSpeedX(float x);
	float getSpeedX();
	void setSpeedY(float y);
	float getSpeedY();
	void setFacingRight(bool state);
	void jump();
	void setJumpState(JumpState state);
	JumpState getJumpState();
	float getJumpingSpeed();
	void setCurrentAction(Action action);
	Action getCurrentAction();
	void setLastFrameAction(Action action);
	Action getLastFrameAction();
	void checkKeyPressedInput();
	void checkKeyDownInput();
	void checkKeyReleasedInput();
	bool getFacingRight();
	void updateMovement();
	void updatePosition();
	bool colliding(RectangleShape rec);
	bool fallingOffPlatform(Platform* platform);
	void updateSprite();
	Sprite getSprite();
};
}

#endif //PLAYER_H
