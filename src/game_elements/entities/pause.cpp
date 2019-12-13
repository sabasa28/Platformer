#include "pause.h"
#include <SFML/Graphics.hpp>
#include "general/game.h"

using namespace sf;

namespace game
{
Pause::Pause(View* camera)
{
	texture.loadFromFile("images/menu_pause.png");
	textureRect = new IntRect(0, 0, SIZE.x, SIZE.y);
	sprite.setTexture(texture);
	sprite.setTextureRect(*textureRect);
	sprite.setPosition({ camera->getCenter().x - SIZE.x / 2.0f, camera->getCenter().y - SIZE.y / 2.0f });
}

Pause::~Pause()
{
}

void Pause::center(View* camera)
{
	sprite.setPosition({ camera->getCenter().x - SIZE.x / 2.0f, camera->getCenter().y - SIZE.y / 2.0f });
}

void Pause::draw()
{
	Game::window->draw(sprite);
}


}

