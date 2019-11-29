#ifndef MELEE_ENEMY
#define MELEE_ENEMY

#include "enemies.h"

enum TargetPos
{
	left,
	right,
	away //a evaluar si se descarta
};

class MeleeEnemy: public Enemy
{
private:
	bool charging;
	const float chargingSpeed = 10.0f;
	const float alertDistance = 200.0f;
public:
	MeleeEnemy();
	~MeleeEnemy();
	bool getChargingState();
	void setChargingState(bool chargeState);
	void updateCharginState();
	TargetPos updateTargetPos(RectangleShape target);
	void updateAwakeState(RectangleShape target);
	void attack(RectangleShape target);
	virtual void Enemy::checkScreenLimits();
};

#endif //MELEE_ENEMY
