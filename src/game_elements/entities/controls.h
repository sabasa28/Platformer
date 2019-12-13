#ifndef CONTROLS_H
#define CONTROLS_H

#include "game_elements/entity.h"
#include "game_states/screen.h"

namespace game 
{
class Controls : public Entity, public Screen {
private:
	const int textRows = 1;
	const float textY = 190.0f;
	const int fontSize = 30;
	const Vector2f recPos = { 3100.0f, -1500.0f };
	const Vector2f recSize = { 600.0f, 400.0f };
public:
	Controls();
	void draw();
	void center(View* camera);
	

};

}
#endif // !CONTROLS_H
