#ifndef PAUSE_H
#define PAUSE_H

#include "game_elements/entity.h"
#include "game_states/screen.h"


namespace game
{
class Pause : public Entity, public Screen{
private:
	const int TEXT_ROWS = 4;
	const float TEXT_Y = 100;
	const int FONT_SIZE = 30;
	const int SPACE_BETWEEN_TEXT = 20;
	const Vector2f POS = { 250.0f, 100.0f };
	const Vector2f SIZE = { 400.0f, 200.0f };
public:
	Pause();
	void center(View* camera);
	void draw();
};
}
#endif //PAUSE_H