#ifndef GOLD_COIN_H
#define GOLD_COIN_H

#include <SFML/Graphics.hpp>

#include "game_elements/entity.h"
#include "game_elements/entities/platform.h"

using namespace sf;

namespace game
{
class GoldCoin : public Entity
{
	static const int SIZE = 50;
	const int SPRITE_SIZE = SIZE;

public:
	GoldCoin();
	~GoldCoin();
};
}

#endif //GOLD_COIN_H