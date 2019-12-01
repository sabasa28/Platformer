#include "player.h"

#include <SFML/Graphics.hpp>

#include "general/game.h"

#include <cmath>

float disToPlat1;
float disToPlat2;

Player::Player()
{
	rectangle.setSize({ static_cast<float>(PLAYER_SIZE), static_cast<float>(PLAYER_SIZE) });
	rectangle.setFillColor(Color::Blue);
	rectangle.setPosition(PLATFORM_SIZE + PLAYER_SIZE/2, static_cast<float>(SCREEN_HEIGHT - PLATFORM_SIZE - rectangle.getSize().y));
	texture.loadFromFile("images/adventurer_spritesheet.png");
	textureRect = new IntRect(0, 0, PLAYER_SPRITE_SIZE, PLAYER_SPRITE_SIZE);
	sprite.setTexture(texture);
	sprite.setTextureRect(*textureRect);
	sprite.setPosition(rectangle.getPosition().x - (PLAYER_SPRITE_SIZE - PLAYER_SIZE) / 2, rectangle.getPosition().y - 60);
	timer = timer.Zero;
	currentAction = standing_action;
	lastFrameAction = standing_action;
	movement.right = false;
	movement.left = false;
	facingRight = true;
	speed = { 0,0 };
	jumping = false;
	jumpState = falling;
}

Player::~Player()
{
}

void Player::setRecPos(float x, float y)
{
	rectangle.setPosition(x, y);
}

void Player::setRecPos(Vector2f pos) 
{
	rectangle.setPosition(pos);
}

void Player::setRecX(float x)
{
	rectangle.setPosition(x, rectangle.getPosition().y);
}

void Player::setRecY(float y)
{
	rectangle.setPosition(rectangle.getPosition().x, y);
}

void Player::addToRecX(float x)
{
	rectangle.setPosition(rectangle.getPosition().x + x, rectangle.getPosition().y);
}

void Player::addToRecY(float y)
{
	rectangle.setPosition(rectangle.getPosition().x, rectangle.getPosition().y + y);
}

void Player::setSpeedY(float y) 
{
	speed.y = y;
}

void Player::setSpeedX(float x)
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

RectangleShape Player::getRec()
{
	return rectangle;
}

Sprite Player::getSprite()
{
	return sprite;
}

void Player::setCurrentAction(Action action)
{
	currentAction = action;
}

Action Player::getCurrentAction()
{
	return currentAction;
}

void Player::setLastFrameAction(Action action)
{
	lastFrameAction = action;
}

Action Player::getLastFrameAction()
{
	return lastFrameAction;
}

float Player::getSpeedY()
{
	return speed.y;
}

JumpState Player::getJumpState()
{
	return jumpState;
}

float Player::getJumpingSpeed()
{
	return jumpingSpeed;
}

void Player::checkKeyPressedInput()
{
	if (Keyboard::isKeyPressed(Keyboard::Right))
	{
		setMoveRight(true);
		setFacingRight(true);
		if (getJumpState() == onGround)
		{
			setCurrentAction(walking_action);
		}
	}
	else
	{
		if (getJumpState() == onGround)
		{
			setCurrentAction(standing_action);
		}
	}

	if (Keyboard::isKeyPressed(Keyboard::Left))
	{
		setMoveLeft(true);
		setFacingRight(false);
		if (getJumpState() == onGround)
		{
			setCurrentAction(walking_action);
		}
	}
}

void Player::checkKeyDownInput()
{
	Game::window->setKeyRepeatEnabled(false);

	if (Keyboard::isKeyPressed (Keyboard::Escape))
	{
		Game::window->close();
	}

	if (Keyboard::isKeyPressed(Keyboard::Space))
	{
		jump();
		setCurrentAction(Action::jumping_action);
	}

	Game::window->setKeyRepeatEnabled(true);
}

void Player::checkKeyReleasedInput()
{
	if (!Keyboard::isKeyPressed(Keyboard::Right))
	{
		setMoveRight(false);
	}

	if (!Keyboard::isKeyPressed(Keyboard::Left))
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

void Player::setFacingRight(bool state)
{
	facingRight = state;
}

bool Player::getFacingRight()
{
	return facingRight;
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
	//if (getUpperSide() < 0)
	//{
	//	setSpeedY(0);
	//	setRecY(0);
	//	jumpState = falling;
	//}

	if (getBottomSide() > SCREEN_HEIGHT)
	{
		setRecY(SCREEN_HEIGHT - rectangle.getSize().y);
		jumpState = onGround;
	}

	//if (getLeftSide() < 0)
	//{
	//	setRecX(0);
	//}
	//
	//if (getRightSide() > SCREEN_WIDTH)
	//{
	//	setRecX(SCREEN_WIDTH - rectangle.getSize().x);
	//}
}

bool Player::colliding(RectangleShape rec)
{
	if (getRec().getGlobalBounds().intersects(rec.getGlobalBounds()))
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

float Player::getUpperSide()
{
	return rectangle.getPosition().y;
}

float Player::getBottomSide()
{
	return getUpperSide() + rectangle.getSize().y;
}

float Player::getLeftSide()
{
	return rectangle.getPosition().x;
}

float Player::getRightSide()
{
	return getLeftSide() + rectangle.getSize().x;
}

float Player::getCenterX()
{
	return getLeftSide() + rectangle.getSize().x / 2;
}

float Player::getCenterY()
{
	return getUpperSide() + rectangle.getSize().y / 2;
}

void Player::updateSprite()
{
	//cout << timer.asMilliseconds() << endl;

	switch (currentAction)
	{
	case standing_action:
		if (facingRight)
		{
			if (lastFrameAction != standing_action)
			{
				textureRect = new IntRect(0, 0, PLAYER_SPRITE_SIZE, PLAYER_SPRITE_SIZE);
				sprite.setTextureRect(*textureRect);
				sprite.setScale(1, 1);
			}

			sprite.setPosition(rectangle.getPosition().x - (PLAYER_SPRITE_SIZE - PLAYER_SIZE) / 2, rectangle.getPosition().y - 60);
		}
		else
		{
			if (lastFrameAction != standing_action)
			{
				textureRect = new IntRect(0, 0, PLAYER_SPRITE_SIZE, PLAYER_SPRITE_SIZE);
				sprite.setTextureRect(*textureRect);
				sprite.setScale(-1, 1);
			}

			sprite.setPosition(rectangle.getPosition().x + (PLAYER_SPRITE_SIZE + PLAYER_SIZE) / 2, rectangle.getPosition().y - 60);
		}
		break;
	case walking_action:
		if (facingRight)
		{
			if (lastFrameAction != walking_action)
			{
				clock.restart().Zero;

				textureRect = new IntRect(0, PLAYER_SPRITE_SIZE, PLAYER_SPRITE_SIZE, PLAYER_SPRITE_SIZE * 2);
				sprite.setTextureRect(*textureRect);
				sprite.setScale(1, 1);
			}

			timer = clock.getElapsedTime();
			sprite.setPosition(rectangle.getPosition().x - (PLAYER_SPRITE_SIZE - PLAYER_SIZE) / 2, rectangle.getPosition().y - 60);
		}
		else
		{
			if (lastFrameAction != walking_action)
			{
				clock.restart().Zero;

				textureRect = new IntRect(0, PLAYER_SPRITE_SIZE, PLAYER_SPRITE_SIZE, PLAYER_SPRITE_SIZE * 2);
				sprite.setTextureRect(*textureRect);
				sprite.setScale(-1, 1);
			}

			timer = clock.getElapsedTime();
			sprite.setPosition(rectangle.getPosition().x + (PLAYER_SPRITE_SIZE + PLAYER_SIZE) / 2, rectangle.getPosition().y - 60);
		}

		if (timer >= milliseconds(125))
		{
			if (textureRect->left == 0)
			{
				textureRect = new IntRect(PLAYER_SPRITE_SIZE, PLAYER_SPRITE_SIZE, PLAYER_SPRITE_SIZE * 2, PLAYER_SPRITE_SIZE * 2);
				sprite.setTextureRect(*textureRect);
				clock.restart().Zero;
				cout << "sprite 1" << endl;
			}
			else
			{
				textureRect = new IntRect(0, PLAYER_SPRITE_SIZE, PLAYER_SPRITE_SIZE, PLAYER_SPRITE_SIZE * 2);
				sprite.setTextureRect(*textureRect);
				clock.restart().Zero;
				cout << "sprite 2" << endl;
			}
		}
		break;
	case jumping_action:
		if (facingRight)
		{
			if (lastFrameAction != jumping_action)
			{
				textureRect = new IntRect(PLAYER_SPRITE_SIZE, 0, PLAYER_SPRITE_SIZE * 2, PLAYER_SPRITE_SIZE);
				sprite.setTextureRect(*textureRect);
			}

			sprite.setScale(1, 1);
			sprite.setPosition(rectangle.getPosition().x - (PLAYER_SPRITE_SIZE - PLAYER_SIZE) / 2, rectangle.getPosition().y - 60);
		}
		else
		{
			if (lastFrameAction != jumping_action)
			{
				textureRect = new IntRect(PLAYER_SPRITE_SIZE, 0, PLAYER_SPRITE_SIZE * 2, PLAYER_SPRITE_SIZE);
				sprite.setTextureRect(*textureRect);
			}

			sprite.setScale(-1, 1);
			sprite.setPosition(rectangle.getPosition().x + (PLAYER_SPRITE_SIZE + PLAYER_SIZE) / 2, rectangle.getPosition().y - 60);
		}
		break;
	}
}