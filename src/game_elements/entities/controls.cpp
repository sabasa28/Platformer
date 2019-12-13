#include "game_elements/entities/controls.h"
#include "general/game.h"

namespace game 
{
	Controls::Controls()
	{
		text.resize(TEXT_ROWS);
		for (int i = 0; i < TEXT_ROWS; i++)
		{
			text[i] = NULL;
		}

		text[0] = new DisplayText("CONTROLS", true, TEXT_Y, Color::Yellow, FONT_SIZE);

	textureRect = NULL;
	rectangle.setFillColor(Color::Black);
	rectangle.setSize(REC_SIZE);
	rectangle.setPosition(REC_POS);
}

void Controls::draw() 
{
	Game::window->draw(rectangle);
	for (int i = 0; i < TEXT_ROWS; i++)
	{
		if (text[i]) text[i]->draw();
	}
}

void Controls::center(View* camera)
{
	if (text[0]) text[0]->setPosition({ camera->getCenter().x - text[0]->getTextWidth() / 2.0f, camera->getCenter().y - TEXT_Y });
	rectangle.setPosition({ camera->getCenter().x - REC_SIZE.x / 2.0f, camera->getCenter().y - REC_SIZE.y / 2.0f });
}

}