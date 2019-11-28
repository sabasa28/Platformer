#ifndef GAME_OVER_H
#define GAME_OVER_H

#include <SFML/Graphics.hpp>

class GameOver
{
	Text* text;

public:
	GameOver();
	~GameOver();
	void checkKeyPressedInput();
	void update();
	void draw();
};

#endif //GAME_OVER_H