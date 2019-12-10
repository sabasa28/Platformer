#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>

using namespace sf;

namespace game
{
class Entity
{
	RectangleShape rectangle;
	Texture texture;
	IntRect* textureRect;
	Sprite sprite;

public:
	Entity();
	Entity(RectangleShape rec, Texture tex, IntRect* texRec, Sprite spr);
	~Entity();
	void setRecPosition(float x, float y);
	void setRecPosition(Vector2f pos);
	void setRecPositionX(float x);
	void setRecPositionY(float y);
	RectangleShape getRec();
	Vector2f getPosition();
	float getPositionX();
	float getPositionY();
	float getUpperSide();
	float getBottomSide();
	float getLeftSide();
	float getRightSide();
	float getCenterX();
	float getCenterY();
	Sprite getSprite();
	void addToPosition(float x, float y);
	void addToPosition(Vector2f pos);
	void addToPositionX(float x);
	void addToPositionY(float y);
	virtual void draw() = 0;
};
}

#endif // !ENTITY_H