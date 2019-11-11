#include "player.h"

#include <SFML/Graphics.hpp>

#include "general/game.h"

Player::Player()
{
	speed = { 0,0 };
	movement.right = false;
	movement.left = false;
	rectangle.setSize({ 50, 50 });
	rectangle.setFillColor(Color::Blue);
	rectangle.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT - rectangle.getSize().y);
	jumpState = onGround;
	jumping = false;
}

Player::~Player()
{
}

void Player::setRecPos(int x, int y)
{
	rectangle.setPosition(x, y);
}

void Player::setRecPos(Vector2f pos) 
{
	rectangle.setPosition(pos);
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

void Player::setSpeedY(int y) 
{
	speed.y = y;
}

void Player::setSpeedX(int x)
{
	speed.x = x;
}

float Player::getSpeedX()
{
	return speed.x;
}

Vector2f Player::getSpeed()
{
	return speed;
}

float Player::getSpeedY()
{
	return speed.y;
}

RectangleShape Player::getRec()
{
	return rectangle;
}

JumpState Player::getJumpState()
{
	return jumpState;
}

float Player::getJumpingSpeed()
{
	return jumpingSpeed;
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

void Player::checkKeyDownInput(Event event, RenderWindow &window)
{
	window.setKeyRepeatEnabled(false);

	if (event.key.code == Keyboard::Escape)
	{
		window.close();
	}

	if (event.key.code == Keyboard::Space)
	{
		jump();
	}

	window.setKeyRepeatEnabled(true);
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

void Player::jump()
{
	if (jumpState == onGround)
	{
		jumpState = start;
	}
}

void Player::setJumpState(JumpState state)
{
	jumpState = state;
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
	
	switch (jumpState)
	{
	case onGround:
		speed.y = 0;
		break;
	case start:
		speed.y -= jumpingSpeed;
		jumpState = ascending;
	case ascending:
		if (speed.y > 0)
		{
			jumpState = falling;
		}
	case falling:
		speed.y += gravity;
		break;
	}

	if (speed.y > MAXIMUM_SPEED)
	{
		speed.y = MAXIMUM_SPEED;
	}

}

void Player::updatePosition() 
{
	rectangle.setPosition(rectangle.getPosition() + speed);
}

void Player::checkScreenLimits()
{
	if (upperSide() < 0)
	{
		setSpeedY(0);
		setRecY(0);
		jumpState = falling;
	}

	if (bottomSide() > SCREEN_HEIGHT)
	{
		setRecY(SCREEN_HEIGHT - rectangle.getSize().y);
		jumpState = onGround;
	}

	if (leftSide() < 0)
	{
		setRecX(0);
	}

	if (rightSide() > SCREEN_WIDTH)
	{
		setRecX(SCREEN_WIDTH - rectangle.getSize().x);
	}
}

bool Player::collidingWithPlatform(Platform* platform)
{
	if (rightSide()>platform->leftSide()&&leftSide()<platform->rightSide())
	{
		if (bottomSide()>platform->upperSide()&& upperSide() < platform->bottomSide())
		{
			return true;
		}
	}
	return false;
}

bool Player::fallingOffPlatform(Platform* platform)
{
	if ((getRec().getPosition().y == platform->upperSide() - getRec().getSize().y)
		&&
		(leftSide() > platform->rightSide() || rightSide() < platform->leftSide()))
	{
		return true;
	}
	else
	{
		return false;
	}
}

int Player::upperSide()
{
	return rectangle.getPosition().y;
}

int Player::bottomSide()
{
	return upperSide() + rectangle.getSize().y;
}

int Player::leftSide()
{
	return rectangle.getPosition().x;
}

int Player::rightSide()
{
	return leftSide() + rectangle.getSize().x;
}