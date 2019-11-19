#include "meleeEnemy.h"

#include <cmath>

#include "general/game.h"

MeleeEnemy::MeleeEnemy()
{
	charging = false;
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

void MeleeEnemy::checkScreenLimits()
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