#ifndef SCREENS_H
#define SCREENS_H

#include <vector>

#include "game_elements/entities/display_text.h"

using namespace std;

namespace game
{

class Screen
{
protected:
	vector <DisplayText*> text;

public:
	void drawText();
};
}

#endif
