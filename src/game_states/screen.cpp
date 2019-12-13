#include "screen.h"

namespace game
{

Screen::~Screen()
{
	for (unsigned int i = 0; i < text.size(); i++)
	{
		if (text[i]) delete text[i];
	}
}

void Screen::drawText()
{
	for (unsigned int i = 0; i < text.size(); i++)
	{
		text[i]->draw();
	}
}
}