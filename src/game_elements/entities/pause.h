#ifndef PAUSE_H
#define PAUSE_H

#include "game_elements/entity.h"
#include "game_states/screen.h"


namespace game
{
class Pause : public Entity
{
	const Vector2i SIZE = { 417, 417 };

public:
	Pause(View* camera);
	~Pause();
	void center(View* camera);
	void draw();
};
}
#endif //PAUSE_H