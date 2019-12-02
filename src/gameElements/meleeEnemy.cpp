#include "meleeEnemy.h"

#include <cmath>

#include "general/game.h"

MeleeEnemy::MeleeEnemy()
{
	charging = false;
	texture.loadFromFile("images/slimeBlock_spritesheet.png");
	textureRect = new IntRect(0, 0, ENEMY_SPRITE_SIZE, ENEMY_SPRITE_SIZE);
	sprite.setTexture(texture);
	sprite.setTextureRect(*textureRect);
	sprite.setPosition(getRec().getPosition().x - (ENEMY_SPRITE_SIZE - ENEMY_SIZE) / 2, getRec().getPosition().y - (ENEMY_SPRITE_SIZE - ENEMY_SIZE) / 2);
}

MeleeEnemy::MeleeEnemy(Vector2f pos):Enemy(pos)
{
	charging = false;
	texture.loadFromFile("images/slimeBlock_spritesheet.png");
	textureRect = new IntRect(0, 0, ENEMY_SPRITE_SIZE, ENEMY_SPRITE_SIZE);
	sprite.setTexture(texture);
	sprite.setTextureRect(*textureRect);
	sprite.setPosition(getRec().getPosition().x - (ENEMY_SPRITE_SIZE - ENEMY_SIZE) / 2, getRec().getPosition().y - 60);
}

MeleeEnemy::~MeleeEnemy()
{
}

bool MeleeEnemy::getChargingState()
{
	return charging;
}

void MeleeEnemy::setChargingState(bool chargeState)
{
	charging = chargeState;
}

void MeleeEnemy::updateCharginState() 
{
	if (Enemy::getSpeed().x == 0.0f && Enemy::getSpeed().y == 0.0f)
	{
		charging = false;
	}
}

TargetPos MeleeEnemy::updateTargetPos(RectangleShape target)
{
	if (abs(Enemy::getRec().getPosition().x - target.getPosition().x) < alertDistance && (Enemy::getUpperSide() < target.getPosition().y + target.getSize().y / 2 && Enemy::getBottomSide() > target.getPosition().y + target.getSize().y / 2))
	{
		if (Enemy::getRec().getPosition().x < target.getPosition().x)
		{
			return TargetPos::right;
		}
		else
		{
			return TargetPos::left;
		}
	}
	else
	{
		return away;
	}
}

void MeleeEnemy::updateAwakeState(RectangleShape target)
{
	if (updateTargetPos(target) != away)
	{
		Enemy::setAwake(true);
	}
}

void MeleeEnemy::attack(RectangleShape target)
{
	if (charging == false && Enemy::getAwake() == true)
	{
		switch (updateTargetPos(target))
		{
		case TargetPos::left:
			Enemy::setSpeed({ -chargingSpeed,0 });
			charging = true;
			break;
		case TargetPos::right:
			Enemy::setSpeed({ chargingSpeed,0 });
			charging = true;
			break;
		case away:
			break;
		}
	}
}

void MeleeEnemy::checkScreenLimits() //SACAR EN CASO DE NO USARLO
{/*
	if (getUpperSide() < 0)
	{
		setSpeedY(0);
		setRecY(0);
		jumpState = falling;
	}*/

	if (getBottomSide() > SCREEN_HEIGHT)
	{
		setRecY(SCREEN_HEIGHT - getRec().getSize().y);
		//jumpState = onGround;
	}

	if (getLeftSide() < 0)
	{
		setRecX(0);
		charging = false;
	}

	if (getRightSide() > SCREEN_WIDTH)
	{
		setRecX(SCREEN_WIDTH - getRec().getSize().x);
		charging = false;
	}
}

void MeleeEnemy::updateSprite()
{
	if (!charging)
	{
		textureRect = new IntRect(0, 0, ENEMY_SPRITE_SIZE, ENEMY_SPRITE_SIZE);
		sprite.setTextureRect(*textureRect);
	}
	else
	{
		textureRect = new IntRect(ENEMY_SPRITE_SIZE, 0, ENEMY_SPRITE_SIZE, ENEMY_SPRITE_SIZE);
		sprite.setTextureRect(*textureRect);
	}

	sprite.setPosition(getRec().getPosition().x - (ENEMY_SPRITE_SIZE - ENEMY_SIZE) / 2, getRec().getPosition().y - (ENEMY_SPRITE_SIZE - ENEMY_SIZE) / 2);
}

Sprite MeleeEnemy::getSprite()
{
	return sprite;
}