#ifndef PLAYER_H
#define PLAYER_H

#include "game_elements/entities/character.h"
#include "game_elements/entities/platform.h"

using namespace sf;

namespace game
{
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

class Player : public Character
{
	const float WIDTH = 50;
	const float HEIGHT = 80;
	Vector2f INITIAL_POS = { 3100.0f, -1500.0f };
	const int SPRITE_SIZE = 128;
	const int SPRITE_Y_SETOFF = 30;
	const float MAXIMUM_SPEED = 1200.0f;//20.0f;
	const float MOVING_SPEED = 600.0f;
	const float COLLISION_MARGIN = 7.0f;
	Movement movement;
	bool facingRight;
	bool jumping;
	JumpState jumpState;
	float jumpingSpeed = 1200.0f;
	Clock clock;
	Time timer;
	Action currentAction;
	Action lastFrameAction;

public:
	Player();
	~Player();
	void setMoveRight(bool state);
	void setMoveLeft(bool state);
	void setFacingRight(bool state);
	void jump();
	void setJumpState(JumpState state);
	JumpState getJumpState();
	float getJumpingSpeed();
	void setCurrentAction(Action action);
	Action getCurrentAction();
	void setLastFrameAction(Action action);
	Action getLastFrameAction();
	float getCollisionMargin();
	void checkKeyPressedInput();
	void checkKeyDownInput();
	void checkKeyReleasedInput();
	bool getFacingRight();
	void updateMovement();
	void updatePosition();
	bool colliding(RectangleShape rec);
	bool fallingOffPlatform(Platform* platform);
	void updateSprite();
};
}

#endif //PLAYER_H
