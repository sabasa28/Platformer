#include "game_elements/entities/controls.h"
#include "general/game.h"

namespace game 
{
Controls::Controls(View* camera)
{
	texture.loadFromFile("images/menu_controls.png");
	textureRect = new IntRect(0, 0, SIZE.x, SIZE.y);
	sprite.setTexture(texture);
	sprite.setTextureRect(*textureRect);
	sprite.setPosition({ camera->getCenter().x - SIZE.x / 2.0f, camera->getCenter().y - SIZE.y / 2.0f });
}

Controls::~Controls()
{
}

void Controls::center(View* camera)
{
	sprite.setPosition({ camera->getCenter().x - SIZE.x / 2.0f, camera->getCenter().y - SIZE.y / 2.0f });
}

void Controls::draw() 
{
	Game::window->draw(sprite);
}
}