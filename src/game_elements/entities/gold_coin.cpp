#include "gold_coin.h"

namespace game
{
GoldCoin::GoldCoin()
{
	rectangle.setSize({ static_cast<float>(SIZE), static_cast<float>(SIZE) });
	rectangle.setPosition({ static_cast<float>( 9100.0f + SIZE / 2), (-2800.0f - SIZE) });
	texture.loadFromFile("images/coin.png");
	textureRect = new IntRect(0, 0, SPRITE_SIZE, SPRITE_SIZE);
	sprite.setTexture(texture);
	sprite.setTextureRect(*textureRect);
	sprite.setPosition(rectangle.getPosition().x - (SPRITE_SIZE - SIZE) / 2, rectangle.getPosition().y);
}

GoldCoin::~GoldCoin()
{
}
}