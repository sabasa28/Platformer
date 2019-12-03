#include "general/game.h"

using namespace game;

int main()
{
	Game* game = new Game();
	game->execute();
	if (game) delete game;

	return 0;
}