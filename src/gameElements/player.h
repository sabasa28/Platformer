#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics.hpp>

using namespace sf;

struct Move
{
	bool right;
	bool left;
	bool up;
	bool down;
};

class Player
{
private:
	RectangleShape rectangle;
	Vector2f speed;
	float jumpingSpeed=10;
	float movingSpeed=10;
	Move move;

public:
	Player();
	~Player();
	void setRecPos(int x, int y);
	void setRecX(int x);
	void setRecY(int y);
	void addToRecX(int x);
	void addToRecY(int y);
	RectangleShape getRec();
	void setMoveRight(bool state);
	void setMoveLeft(bool state);
	void setMoveUp(bool state);
	void setMoveDown(bool state);
	void updateMovement();
	int bottomSide();
	int upSide();
	int rightSide();
	int leftSide();

};

#endif //PLAYER_H
