#include "meleeEnemy.h"

MeleeEnemy::MeleeEnemy()
{
	charging = false;
	targetPos = left;
}

MeleeEnemy::~MeleeEnemy()
{
}

TargetPos MeleeEnemy::getTargetPos()
{
	return targetPos;
}

bool MeleeEnemy::getChargingState()
{
	return charging;
}

void MeleeEnemy::updateTargetPos(RectangleShape target)
{
	if (Enemy::getRec().getPosition().x < target.getPosition().x)
	{
		targetPos = right;
	}
	else
	{
		targetPos = left;
	}
}

void MeleeEnemy::setChargingState(bool chargeState)
{
	charging = chargeState;
}