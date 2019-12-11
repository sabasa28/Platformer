#ifndef SLIME_BLOCK_H
#define SLIME_BLOCK_H

#include "gameElements/entities/characters/enemy.h"

namespace game
{

enum TargetPos
{
	left,
	right,
	away
};

class SlimeBlock: public Enemy
{
	const int SPRITE_SIZE = 64;

	bool charging;
	const float chargingSpeed = 10.0f;
	const float alertDistance = 200.0f;

public:
	SlimeBlock();
	SlimeBlock(Vector2f pos);
	~SlimeBlock();
	void setChargingState(bool chargeState);
	bool getChargingState();
	void updateCharginState();
	TargetPos updateTargetPos(RectangleShape target);
	void updateAwakeState(RectangleShape target);
	void attack(RectangleShape target);
	void updateSprite();
};
}

#endif //MELEE_ENEMY
