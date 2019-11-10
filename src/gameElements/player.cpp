#include "player.h"

#include "general/game.h"

#include <iostream>
using namespace std;

Player::Player()
{
	speed = { 0,0 };
	movement.right = false;
	movement.left = false;
	rectangle.setSize({ 50, 50 });
	rectangle.setFillColor(Color::Blue);
	rectangle.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT - rectangle.getSize().y);
	jumpstate = onGround;
	jumping = false;
}

Player::~Player()
{

}

void Player::setRecPos(int x, int y)
{
	rectangle.setPosition(x, y);
}

void Player::setRecX(int x)
{
	rectangle.setPosition(x, rectangle.getPosition().y);
}

void Player::setRecY(int y)
{
	rectangle.setPosition(rectangle.getPosition().x, y);
}

void Player::addToRecX(int x)
{
	rectangle.setPosition(rectangle.getPosition().x + x, rectangle.getPosition().y);
}

void Player::addToRecY(int y)
{
	rectangle.setPosition(rectangle.getPosition().x, rectangle.getPosition().y + y);
}

RectangleShape Player::getRec()
{
	return rectangle;
}

JumpState Player::getJumpstate()
{
	return jumpstate;
}

void Player::checkKeyPressedInput(Event event)
{
	if (event.key.code == Keyboard::Right)
	{
		setMoveRight(true);
	}
	if (event.key.code == Keyboard::Left)
	{
		setMoveLeft(true);
	}
}

void Player::checkKeyReleasedInput(Event event)
{
	if (event.key.code == Keyboard::Right)
	{
		setMoveRight(false);
	}
	if (event.key.code == Keyboard::Left)
	{
		setMoveLeft(false);
	}
}

void Player::setMoveRight(bool state)
{
	movement.right = state;
}

void Player::setMoveLeft(bool state)
{
	movement.left = state;
}

void Player::setJump(bool state)
{
	if (jumpstate == onGround)
	{
		jumpstate = start;
	}
}

void Player::setJumpstate(JumpState state)
{
	jumpstate = state;
}

void Player::updateMovement()
{
	speed.x = 0.0f;
	
	if (movement.right)
	{
		speed.x += movingSpeed;
	}
	if (movement.left)
	{
		speed.x -= movingSpeed;
	}
	
	switch (jumpstate)
	{
	case onGround:
		speed.y = 0;
		break;
	case start:
		speed.y -= jumpingSpeed;
		jumpstate = midAir;
	case midAir:
		if (speed.y>0)
		{
			jumpstate=falling;
		}
	case falling:
		speed.y += gravity;
		break;
	}

	if (speed.y > MAXIMUM_SPEED)
	{
		speed.y = MAXIMUM_SPEED;
	}
	
	rectangle.setPosition(rectangle.getPosition() + speed);

	checkScreenLimits();
}

void Player::checkScreenLimits()
{
	if (rectangle.getPosition().y + rectangle.getSize().y > SCREEN_HEIGHT)
	{
		setRecY(SCREEN_HEIGHT - rectangle.getSize().y);
		jumpstate = onGround;
		gravity = GRAVITY_INITIAL_VALUE;
	}

	if (rectangle.getPosition().x < 0)
	{
		setRecX(0);
	}

	if (rectangle.getPosition().x + rectangle.getSize().x > SCREEN_WIDTH)
	{
		setRecX(SCREEN_WIDTH - rectangle.getSize().x);
	}
}

int Player::bottomSide()
{
	return rectangle.getPosition().y + rectangle.getSize().y;
}

int Player::upperSide()
{
	return rectangle.getPosition().y;
}

int Player::rightSide()
{
	return rectangle.getPosition().x + rectangle.getSize().x;
}

int Player::leftSide()
{
	return rectangle.getPosition().x;
}