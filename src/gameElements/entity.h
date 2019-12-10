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
	void setPosition(Vector2f pos);
	void setPositionX(float x);
	void setPositionY(float y);
	int getPosition();
	int getPositionX();
	int getPositionY();
	void addToPosition(Vector2 pos);
	void addToPositionX(float x);
	void addToPositionY(float y);
	float getUpperSide();
	float getBottomSide();
	float getLeftSide();
	float getRightSide();
	float getCenterX();
	float getCenterY();
};
}

#endif // !ENTITY_H