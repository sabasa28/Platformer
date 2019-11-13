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
	TargetPos targetPos;

public:
	MeleeEnemy();
	~MeleeEnemy();
	TargetPos getTargetPos();
	bool getChargingState();
	void updateTargetPos(RectangleShape target);
	void setChargingState(bool chargeState);
};

#endif //MELEE_ENEMY
