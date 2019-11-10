#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics.hpp>

using namespace sf;

const float MAXIMUM_SPEED = 20;
const float GRAVITY_INITIAL_VALUE = 1.001;
const float GRAVITY_MULTIPLIER = 1.2;

struct Movement
{
	bool right;
	bool left;
};

class Player
{
private:
	RectangleShape rectangle;
	Vector2f speed;
	bool jumping;
	float jumpingSpeed = 20;
	float movingSpeed = 10;
	float gravity = GRAVITY_INITIAL_VALUE;
	Movement movement;

public:
	Player();
	~Player();
	void setRecPos(int x, int y);
	void setRecX(int x);
	void setRecY(int y);
	void addToRecX(int x);
	void addToRecY(int y);
	RectangleShape getRec();
	void checkKeyPressedInput(Event event);
	void checkKeyReleasedInput(Event event);
	void setMoveRight(bool state);
	void setMoveLeft(bool state);
	void setJump(bool state);
	void updateMovement();
	void checkScreenLimits();
	int bottomSide();
	int upperSide();
	int rightSide();
	int leftSide();
};

#endif //PLAYER_H
