#ifndef MELEE_ENEMY
#define MELEE_ENEMY

#include "enemies.h"

namespace game
{
const int ENEMY_SPRITE_SIZE = 64;

enum TargetPos
{
	left,
	right,
	away //a evaluar si se descarta
};

class MeleeEnemy: public Enemy
{
	bool charging;
	const float chargingSpeed = 10.0f;
	const float alertDistance = 200.0f;
	Texture texture;
	IntRect* textureRect;
	Sprite sprite;

public:
	MeleeEnemy();
	MeleeEnemy(Vector2f pos);
	~MeleeEnemy();
	void setChargingState(bool chargeState);
	bool getChargingState();
	void updateCharginState();
	TargetPos updateTargetPos(RectangleShape target);
	void updateAwakeState(RectangleShape target);
	void attack(RectangleShape target);
	void updateSprite();
	Sprite getSprite();
};
}

#endif //MELEE_ENEMY
