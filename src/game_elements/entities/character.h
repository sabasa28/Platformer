#ifndef CHARACTER_H
#define CHARACTER_H

#include "game_elements/entity.h"

namespace game
{
class Character : public Entity
{
protected:
	const float GRAVITY = 0.75f;

	Vector2f speed;

public:
	Character();
	Character(float x, float y, RectangleShape rec, Texture tex, IntRect* texRec, Sprite spr);
	Character(Vector2f spe, RectangleShape rec, Texture tex, IntRect* texRec, Sprite spr);
	~Character();
	void setSpeed(float x, float y);
	void setSpeed(Vector2f spe);
	void setSpeedX(float x);
	void setSpeedY(float y);
	Vector2f getSpeed();
	float getSpeedX();
	float getSpeedY();
	virtual void updateSprite() = 0;
};
}

#endif // !CHARACTER_H