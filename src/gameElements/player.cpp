#include "player.h"

#include <SFML/Graphics.hpp>

#include "general/game.h"

#include <cmath>

float disToPlat1;
float disToPlat2;

Player::Player()
{
	rectangle.setSize({ static_cast<float>(PLAYER_WIDTH), static_cast<float>(PLAYER_HEIGHT) });
	rectangle.setFillColor(Color::Blue);
	rectangle.setPosition(PLATFORM_SIZE + PLAYER_WIDTH/2, static_cast<float>(SCREEN_HEIGHT - PLATFORM_SIZE - rectangle.getSize().y));
	movement.right = false;
	movement.left = false;
	facingRight = true;
	speed = { 0,0 };
	jumping = false;
	jumpState = falling;
	texture.loadFromFile("images/adventurer_spritesheet.png");
	textureRect = new IntRect(0, 0, PLAYER_SPRITE_SIZE, PLAYER_SPRITE_SIZE);
	sprite.setTexture(texture);
	sprite.setTextureRect(*textureRect);
	sprite.setPosition(rectangle.getPosition().x - (PLAYER_SPRITE_SIZE - PLAYER_WIDTH) / 2, rectangle.getPosition().y - PLAYER_SPRITE_Y_SETOFF);
	timer = timer.Zero;
	currentAction = standing_action;
	lastFrameAction = standing_action;
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
	
	if (Keyboard::isKeyPressed(Keyboard::Left))
	{
		setMoveLeft(true);
		
		if (!Keyboard::isKeyPressed(Keyboard::Right))
		{
			setFacingRight(false);
		}
		if (getJumpState() == onGround)
		{
			setCurrentAction(walking_action);
		}
	}

	if (((Keyboard::isKeyPressed(Keyboard::Left) && Keyboard::isKeyPressed(Keyboard::Right))
		||
		(!Keyboard::isKeyPressed(Keyboard::Left) && !Keyboard::isKeyPressed(Keyboard::Right)))
		&&
		getJumpState() == onGround)
	{
		setCurrentAction(standing_action);
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
	switch (currentAction)
	{
	case standing_action:
	{
		cout << "standing" << endl;
		if (lastFrameAction != jumping_action)
		{
			if (facingRight)
			{
				textureRect = new IntRect(0, 0, PLAYER_SPRITE_SIZE, PLAYER_SPRITE_SIZE);
				sprite.setTextureRect(*textureRect);
			}
			else
			{
				textureRect = new IntRect(PLAYER_SPRITE_SIZE, 0, PLAYER_SPRITE_SIZE, PLAYER_SPRITE_SIZE);
				sprite.setTextureRect(*textureRect);
			}
		}

		break;
	}
	case jumping_action:
	{
		cout << "jumping" << endl;
			if (facingRight)
			{
				textureRect = new IntRect(PLAYER_SPRITE_SIZE * 2, 0, PLAYER_SPRITE_SIZE, PLAYER_SPRITE_SIZE);
				sprite.setTextureRect(*textureRect);
			}
			else
			{
				textureRect = new IntRect(PLAYER_SPRITE_SIZE * 3, 0, PLAYER_SPRITE_SIZE, PLAYER_SPRITE_SIZE);
				sprite.setTextureRect(*textureRect);
			}

		break;
	}
	case walking_action:
	{
		cout << "walking" << endl;
		if (facingRight)
		{
			if (lastFrameAction != walking_action)
			{
				clock.restart().Zero;

				textureRect = new IntRect(0, PLAYER_SPRITE_SIZE, PLAYER_SPRITE_SIZE, PLAYER_SPRITE_SIZE);
				sprite.setTextureRect(*textureRect);
			}

			timer = clock.getElapsedTime();

			if (timer >= milliseconds(125))
			{
				if (textureRect->left == 0)
				{
					textureRect = new IntRect(PLAYER_SPRITE_SIZE, PLAYER_SPRITE_SIZE, PLAYER_SPRITE_SIZE, PLAYER_SPRITE_SIZE);
					sprite.setTextureRect(*textureRect);
					clock.restart().Zero;
					cout << "sprite 1" << endl;
				}
				else
				{
					textureRect = new IntRect(0, PLAYER_SPRITE_SIZE, PLAYER_SPRITE_SIZE, PLAYER_SPRITE_SIZE);
					sprite.setTextureRect(*textureRect);
					clock.restart().Zero;
					cout << "sprite 2" << endl;
				}
			}
		}
		else
		{
			if (lastFrameAction != walking_action)
			{
				clock.restart().Zero;

				textureRect = new IntRect(PLAYER_SPRITE_SIZE * 2, PLAYER_SPRITE_SIZE, PLAYER_SPRITE_SIZE, PLAYER_SPRITE_SIZE);
				sprite.setTextureRect(*textureRect);
			}

			timer = clock.getElapsedTime();

			if (timer >= milliseconds(125))
			{
				if (textureRect->left == PLAYER_SPRITE_SIZE * 2)
				{
					textureRect = new IntRect(PLAYER_SPRITE_SIZE * 3, PLAYER_SPRITE_SIZE, PLAYER_SPRITE_SIZE, PLAYER_SPRITE_SIZE);
					sprite.setTextureRect(*textureRect);
					clock.restart().Zero;
					cout << "sprite 1" << endl;
				}
				else
				{
					textureRect = new IntRect(PLAYER_SPRITE_SIZE * 2, PLAYER_SPRITE_SIZE, PLAYER_SPRITE_SIZE, PLAYER_SPRITE_SIZE);
					sprite.setTextureRect(*textureRect);
					clock.restart().Zero;
					cout << "sprite 2" << endl;
				}
			}
		}
		break;
	}
	}

	sprite.setPosition(rectangle.getPosition().x - (PLAYER_SPRITE_SIZE - PLAYER_WIDTH) / 2, rectangle.getPosition().y - PLAYER_SPRITE_Y_SETOFF);
}