#ifndef ENEMIES_H
#define ENEMIES_H

#include <SFML/Graphics.hpp>



using namespace sf;

class Enemy
{
private:
	bool alive;
	bool awake;
	RectangleShape rectangle;
	Vector2f speed;

public:
	Enemy();
	~Enemy();
	bool getAlive();
	bool getAwake();
	RectangleShape getRec();
	Vector2f getSpeed();
	void setAlive(bool newAlive);
	void setAwake(bool newAwake);
	void setSpeed(Vector2f newSpeed);
	virtual void attack()=0;
};

#endif // !ENEMIES_H
