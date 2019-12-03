#include "credits.h"

#include "general/game.h"

namespace game
{
Credits::Credits()
{
	for (int i = 0; i < CREDITS_TEXT_ROWS_AMOUNT; i++)
	{
		textRows[i] = NULL;
	}
	textRows[15] = new DisplayText("Press 'Enter' to return to menu", false, SCREEN_HEIGHT- CREDITS_TEXT_SPACING, Color::Yellow, PARAGRAPH_FONT_SIZE);
	textRows[14] = new DisplayText("Audacity 2.3.3 (audacityteam.org)", true, CREDITS_INTIAL_POS, Color::White, PARAGRAPH_FONT_SIZE);
	textRows[13] = new DisplayText("Audio Editing", true, textRows[14]->getUpperSide() - CREDITS_TEXT_SPACING, Color::White, PARAGRAPH_FONT_SIZE);
	textRows[12] = new DisplayText("Adobe Photoshop CC 2019 (photoshop.com)", true, textRows[13]->getUpperSide() - CREDITS_TEXT_SPACING * 2, Color::White, PARAGRAPH_FONT_SIZE);
	textRows[11] = new DisplayText("Image Editing", true, textRows[12]->getUpperSide() - CREDITS_TEXT_SPACING, Color::White, PARAGRAPH_FONT_SIZE);
	textRows[10] = new DisplayText("Kenney (kenney.nl)", true, textRows[11]->getUpperSide() - CREDITS_TEXT_SPACING * 2, Color::White, PARAGRAPH_FONT_SIZE);
	textRows[9] = new DisplayText("All Visual & Audio Assets", true, textRows[10]->getUpperSide() - CREDITS_TEXT_SPACING, Color::White, PARAGRAPH_FONT_SIZE);
	textRows[8] = new DisplayText("SFML (sfml-dev.org)", true, textRows[9]->getUpperSide() - CREDITS_TEXT_SPACING * 2, Color::White, PARAGRAPH_FONT_SIZE);
	textRows[7] = new DisplayText("Engine", true, textRows[8]->getUpperSide() - CREDITS_TEXT_SPACING, Color::White, PARAGRAPH_FONT_SIZE);
	textRows[6] = new DisplayText("Sani (Instagram: @sani_draws)", true, textRows[7]->getUpperSide() - CREDITS_TEXT_SPACING * 2, Color::White, PARAGRAPH_FONT_SIZE);
	textRows[5] = new DisplayText("Interface Music - resamebeleing", true, textRows[6]->getUpperSide() - CREDITS_TEXT_SPACING, Color::White, PARAGRAPH_FONT_SIZE);
	textRows[4] = new DisplayText("Micael \"BlueEagle\" Lucuman (soundcloud.com/blueeagle98)", true ,textRows[5]->getUpperSide() - CREDITS_TEXT_SPACING * 2, Color::White, PARAGRAPH_FONT_SIZE);
	textRows[3] = new DisplayText("Gameplay Music - Friendly Fire", true, textRows[4]->getUpperSide() - CREDITS_TEXT_SPACING, Color::White, PARAGRAPH_FONT_SIZE);
	textRows[2] = new DisplayText("Lucio Ruixo & Iñaki Diez Galarza", true, textRows[3]->getUpperSide() - CREDITS_TEXT_SPACING * 2, Color::White, PARAGRAPH_FONT_SIZE);
	textRows[1] = new DisplayText("Game Programing + Developing", true, textRows[2]->getUpperSide() - CREDITS_TEXT_SPACING, Color::White, PARAGRAPH_FONT_SIZE);
	textRows[0] = new DisplayText("CREDITS", false, CREDITS_TEXT_SPACING/2, Color::Yellow, PARAGRAPH_FONT_SIZE);
}

Credits::~Credits()
{
	for (int i = 0; i < CREDITS_TEXT_ROWS_AMOUNT; i++)
	{
		if (textRows[i]) delete textRows[i];
	}
}

void Credits::checkKeyDownInput()
{
	Game::window->setKeyRepeatEnabled(false);

	if (Keyboard::isKeyPressed(Keyboard::Enter))
	{
		if (!Game::getGameStateInputActive())
		{
			Game::buttonSFX.play();
			Game::setGameStateInputActive(true);
			Game::currentGameState = menu_state;
		}
	}
	else
	{
		if (Game::getGameStateInputActive())
		{
			Game::setGameStateInputActive(false);
		}
	}

	Game::window->setKeyRepeatEnabled(true);
}

void Credits::setInitialPos()
{
	for (int i = 0; i < CREDITS_TEXT_ROWS_AMOUNT; i++)
	{
		if (textRows[i]) textRows[i]->setPositionY(textRows[i]->getInitialPos().y);
	}
}

void Credits::scroll()
{
	for (int i = 0; i < CREDITS_TEXT_ROWS_AMOUNT; i++)
	{
		if (textRows[i])
		{
			if (textRows[i]->getCentered() == true)
			{
				if (textRows[CREDITS_TEXT_ROWS_AMOUNT-2]->getBottomSide()<0)
				{
					setInitialPos();
					break;
				}
				textRows[i]->setPositionY(textRows[i]->getUpperSide()-TEXT_SCROLLING_SPEED);
			}
		}
	}
}

void Credits::update()
{
	checkKeyDownInput();
	scroll();
}

void Credits::draw()
{
	for (int i = 0; i < CREDITS_TEXT_ROWS_AMOUNT; i++)
	{
		if (textRows[i]) textRows[i]->draw();
	}
}
}