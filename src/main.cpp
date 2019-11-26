#include "general/game.h"

int main()
{
	Game* game = new Game();
	game->execute();
	if (game) delete game;
	return 0;
}