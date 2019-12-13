#ifndef CONTROLS_H
#define CONTROLS_H

#include "game_elements/entity.h"
#include "game_states/screen.h"

namespace game 
{
class Controls : public Entity
{
	const Vector2i SIZE = { 417, 417 };

public:
	Controls(View* camera);
	~Controls();
	void center(View* camera);
	void draw();
};
}
#endif // !CONTROLS_H
