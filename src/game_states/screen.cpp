#include "screen.h"

namespace game
{
void Screen::drawText()
{
	for (unsigned int i = 0; i < text.size(); i++)
	{
		text[i]->draw();
	}
}
}