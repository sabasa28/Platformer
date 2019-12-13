#include "pause.h"
#include <SFML/Graphics.hpp>
#include "general/game.h"

using namespace sf;

namespace game
{
Pause::Pause()
{
	text.resize(TEXT_ROWS);
	textureRect = NULL;
	rectangle.setSize(SIZE);
	rectangle.setPosition(POS);
	rectangle.setFillColor(Color::Black);
	for (int i = 0; i < TEXT_ROWS; i++)
	{
		text[i] = NULL;
	}

	text[0] = new DisplayText("PAUSED", true, TEXT_Y, Color::Yellow, FONT_SIZE);
	text[1] = new DisplayText("\"Enter\" to go back to menu", true, text[0]->getBottomSide() + SPACE_BETWEEN_TEXT, Color::White, FONT_SIZE);
	text[2] = new DisplayText("\"M\" to mute/unmute", true, text[1]->getBottomSide() + SPACE_BETWEEN_TEXT, Color::White, FONT_SIZE);
	text[3] = new DisplayText("\"Escape\" to unpause", true, text[2]->getBottomSide() + SPACE_BETWEEN_TEXT, Color::White, FONT_SIZE);

}

void Pause::center(View* camera)
{
	if (text[0]) text[0]->setPosition({ camera->getCenter().x - text[0]->getTextWidth() / 2.0f, camera->getCenter().y - TEXT_Y });
	if (text[1]) text[1]->setPosition({ camera->getCenter().x - text[1]->getTextWidth() / 2.0f, text[0]->getBottomSide() + SPACE_BETWEEN_TEXT });
	if (text[2]) text[2]->setPosition({ camera->getCenter().x - text[2]->getTextWidth() / 2.0f, text[1]->getBottomSide() + SPACE_BETWEEN_TEXT });
	if (text[3]) text[3]->setPosition({ camera->getCenter().x - text[3]->getTextWidth() / 2.0f, text[2]->getBottomSide() + SPACE_BETWEEN_TEXT });

	rectangle.setPosition({ camera->getCenter().x - SIZE.x / 2.0f, camera->getCenter().y - SIZE.y / 2.0f });
}

void Pause::draw()
{
	Game::window->draw(rectangle);

	for (int i = 0; i < TEXT_ROWS; i++)
	{
		if (text[i]) text[i]->draw();
	}
}


}

