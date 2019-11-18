#include "meleeEnemy.h"

#include <cmath>

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
	if (abs(Enemy::getRec().getPosition().x - target.getPosition().x) < alertDistance && Enemy::getUpperSide() < target.getPosition().y + target.getSize().y / 2 && Enemy::getBottomSide() > target.getPosition().y + target.getSize().y / 2)
	{
		if (Enemy::getRec().getPosition().x < target.getPosition().x)
		{
			return right;
		}
		else
		{
			return left;
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
		case left:
			Enemy::setSpeed({ -chargingSpeed,0 });
			charging = true;
			break;
		case right:
			Enemy::setSpeed({ chargingSpeed,0 });
			charging = true;
			break;
		case away:
			break;
		}
	}
}