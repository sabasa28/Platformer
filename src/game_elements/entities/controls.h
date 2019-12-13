#ifndef CONTROLS_H
#define CONTROLS_H

#include "game_elements/entity.h"
#include "game_states/screen.h"

namespace game 
{
class Controls : public Entity, public Screen {
	const int TEXT_ROWS = 1;
	const float TEXT_Y = 190.0f;
	const int FONT_SIZE = 30;
	const Vector2f REC_POS = { 3100.0f, -1500.0f };
	const Vector2f REC_SIZE = { 600.0f, 400.0f };
public:
	Controls();
	void draw();
	void center(View* camera);

};

}
#endif // !CONTROLS_H
