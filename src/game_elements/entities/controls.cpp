#include "game_elements/entities/controls.h"
#include "general/game.h"

namespace game 
{
	Controls::Controls()
	{
		text.resize(textRows);
		for (int i = 0; i < textRows; i++)
		{
			text[i] = NULL;
		}

		text[0] = new DisplayText("CONTROLS", true, textY, Color::Yellow, fontSize);

	textureRect = NULL;
	rectangle.setFillColor(Color::Black);
	rectangle.setSize(recSize);
	rectangle.setPosition(recPos);
}

void Controls::draw() 
{
	Game::window->draw(rectangle);
	for (int i = 0; i < textRows; i++)
	{
		if (text[i]) text[i]->draw();
	}
}

void Controls::center(View* camera)
{
	if (text[0]) text[0]->setPosition({ camera->getCenter().x - text[0]->getTextWidth() / 2.0f, camera->getCenter().y - textY });
	rectangle.setPosition({ camera->getCenter().x - recSize.x / 2.0f, camera->getCenter().y - recSize.y / 2.0f });
}

}