#include "slime_block.h"

#include "general/game.h"

namespace game
{
SlimeBlock::SlimeBlock()
{
	charging = false;
	texture.loadFromFile("images/slimeBlock_spritesheet.png");
	textureRect = new IntRect(0, 0, SPRITE_SIZE, SPRITE_SIZE);
	sprite.setTexture(texture);
	sprite.setTextureRect(*textureRect);
	sprite.setPosition(getRec().getPosition().x - (SPRITE_SIZE - SIZE) / 2, getRec().getPosition().y - (SPRITE_SIZE - SIZE) / 2);
}

SlimeBlock::SlimeBlock(Vector2f pos):Enemy(pos)
{
	charging = false;
	texture.loadFromFile("images/slimeBlock_spritesheet.png");
	textureRect = new IntRect(0, 0, SPRITE_SIZE, SPRITE_SIZE);
	sprite.setTexture(texture);
	sprite.setTextureRect(*textureRect);
	sprite.setPosition(getRec().getPosition().x - (SPRITE_SIZE - SIZE) / 2, getRec().getPosition().y - 60);
}

SlimeBlock::~SlimeBlock()
{
}

void SlimeBlock::setChargingState(bool chargeState)
{
	charging = chargeState;
}

bool SlimeBlock::getChargingState()
{
	return charging;
}

void SlimeBlock::updateCharginState() 
{
	if (Enemy::getSpeed().x == 0.0f && Enemy::getSpeed().y == 0.0f)
	{
		charging = false;
	}
}

float SlimeBlock::getCollisionMargin()
{
	return collisionMargin;
}

TargetPos SlimeBlock::updateTargetPos(RectangleShape target)
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

void SlimeBlock::updateAwakeState(RectangleShape target)
{
	if (updateTargetPos(target) != away)
	{
		setAwake(true);
	}
}

void SlimeBlock::attack(RectangleShape target)
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

void SlimeBlock::updateSprite()
{
	if (!charging)
	{
		textureRect = new IntRect(0, 0, SPRITE_SIZE, SPRITE_SIZE);
		sprite.setTextureRect(*textureRect);
	}
	else
	{
		textureRect = new IntRect(SPRITE_SIZE, 0, SPRITE_SIZE, SPRITE_SIZE);
		sprite.setTextureRect(*textureRect);
	}

	sprite.setPosition(getRec().getPosition().x - (SPRITE_SIZE - SIZE) / 2, getRec().getPosition().y - (SPRITE_SIZE - SIZE) / 2);
}
}