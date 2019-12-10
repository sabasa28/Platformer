#include "melee_enemy.h"

#include "general/game.h"

namespace game
{
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

void MeleeEnemy::setChargingState(bool chargeState)
{
	charging = chargeState;
}

bool MeleeEnemy::getChargingState()
{
	return charging;
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
	if (abs(getRec().getPosition().x - target.getPosition().x) < alertDistance && (getCenter().y > target.getPosition().y && getCenter().y < target.getPosition().y + target.getSize().y))
	{
		if (getRec().getPosition().x < target.getPosition().x)
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
		setAwake(true);
	}
}

void MeleeEnemy::attack(RectangleShape target)
{
	if (charging == false && Enemy::getAwake() == true)
	{
		switch (updateTargetPos(target))
		{
		case TargetPos::left:
			setSpeed({ -chargingSpeed,0 });
			charging = true;
			break;
		case TargetPos::right:
			setSpeed({ chargingSpeed,0 });
			charging = true;
			break;
		case away:
			break;
		}
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
}