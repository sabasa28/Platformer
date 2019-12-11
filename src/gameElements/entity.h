#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>

using namespace sf;

namespace game
{
class Entity
{
protected:
	RectangleShape rectangle;
	Texture texture;
	IntRect* textureRect;
	Sprite sprite;

public:
	Entity();
	Entity(RectangleShape rec, Texture tex, IntRect* texRec, Sprite spr);
	~Entity();
	void setRecPos(float x, float y);
	void setRecPos(Vector2f pos);
	void setRecPosX(float x);
	void setRecPosY(float y);
	RectangleShape getRec();
	Vector2f getRecPos();
	float getRecPosX();
	float getRecPosY();
	float getUpperSide();
	float getBottomSide();
	float getLeftSide();
	float getRightSide();
	Vector2f getCenter();
	float getCenterX();
	float getCenterY();
	Sprite getSprite();
	void addToPosition(float x, float y);
	void addToPosition(Vector2f pos);
	void addToPositionX(float x);
	void addToPositionY(float y);
};
}

#endif // !ENTITY_H