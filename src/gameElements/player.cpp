#include "player.h"

Player::Player()
{
	speed = { 0,0 };
	move.right = false;
	move.left = false;
	move.up = false;
	move.down = false;
	rectangle.setSize({ 50, 50 });
	rectangle.setFillColor(Color::Blue);
	rectangle.setPosition(100, 100);
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
	rectangle.setPosition(rectangle.getPosition().x, rectangle.getPosition().y+y);
}

RectangleShape Player::getRec()
{
	return rectangle;
}

void Player::setMoveRight(bool state)
{
	move.right = state;
}

void Player::setMoveLeft(bool state)
{
	move.left = state;
}

void Player::setMoveUp(bool state)
{
	move.up = state;
}

void Player::setMoveDown(bool state)
{
	move.down = state;
}

void Player::updateMovement()
{
	speed = { 0,0 };
	
	if (move.right)
	{
		speed.x += movingSpeed;
	}
	if (move.left)
	{
		speed.x -= movingSpeed;
	}
	if (move.up)
	{
		speed.y -= movingSpeed;
	}
	if (move.down)
	{
		speed.y += movingSpeed;
	}
	rectangle.setPosition(rectangle.getPosition()+speed);
}
