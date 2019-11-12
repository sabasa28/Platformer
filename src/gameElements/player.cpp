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
	if (Keyboard::isKeyPressed(Keyboard::Right))
	{
		setMoveRight(true);
	}
	if (Keyboard::isKeyPressed(Keyboard::Left))
	{
		setMoveLeft(true);
	}
}

void Player::checkKeyDownInput(Event event, RenderWindow* &window)
{
	window->setKeyRepeatEnabled(false);

	if (Keyboard::isKeyPressed (Keyboard::Escape))
	{
		window->close();
	}

	if (Keyboard::isKeyPressed(Keyboard::Space))
	{
		jump();
	}

	window->setKeyRepeatEnabled(true);
}

void Player::checkKeyReleasedInput(Event event)
{
	if (!Keyboard::isKeyPressed (Keyboard::Right))
	{
		setMoveRight(false);
	}
	if (!Keyboard::isKeyPressed (Keyboard::Left))
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
	if (getUpperSide() < 0)
	{
		setSpeedY(0);
		setRecY(0);
		jumpState = falling;
	}

	if (getBottomSide() > SCREEN_HEIGHT)
	{
		setRecY(SCREEN_HEIGHT - rectangle.getSize().y);
		jumpState = onGround;
	}

	if (getLeftSide() < 0)
	{
		setRecX(0);
	}

	if (getRightSide() > SCREEN_WIDTH)
	{
		setRecX(SCREEN_WIDTH - rectangle.getSize().x);
	}
}

bool Player::colliding(RectangleShape rectangle)
{
	if (getRec().getGlobalBounds().intersects(rectangle.getGlobalBounds()))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Player::fallingOffPlatform(Platform* platform)
{
	if ((getRec().getPosition().y == platform->getUpperSide() - getRec().getSize().y)
		&&
		(getLeftSide() > platform->getRightSide() || getRightSide() < platform->getLeftSide()))
	{
		return true;
	}
	else
	{
		return false;
	}
}

int Player::getUpperSide()
{
	return rectangle.getPosition().y;
}

int Player::getBottomSide()
{
	return getUpperSide() + rectangle.getSize().y;
}

int Player::getLeftSide()
{
	return rectangle.getPosition().x;
}

int Player::getRightSide()
{
	return getLeftSide() + rectangle.getSize().x;
}