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
	const int WIDTH = 50;
	const int HEIGHT = 80;
	const int INITIAL_POSITION = Platform::getSize() * 21;
	const int SPRITE_SIZE = 128;
	const int SPRITE_Y_SETOFF = 30;
	const float MAXIMUM_SPEED = 20.0f;

	Movement movement;
	bool facingRight;
	float movingSpeed = 10.0f;
	bool jumping;
	JumpState jumpState;
	float jumpingSpeed = 20.0f;
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
