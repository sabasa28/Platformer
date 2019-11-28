#include "gameover.h"

#include "general/game.h"

GameOver::GameOver()
{
	text = new Text("GAME OVER", Game::generalFont);
}

GameOver::~GameOver()
{
}

void GameOver::checkKeyPressedInput()
{
	if (Keyboard::isKeyPressed(Keyboard::Enter))
	{
		Game::changeGamestate(menu_state);
	}
}

void GameOver::update()
{
	checkKeyPressedInput();
}

void GameOver::draw()
{

}