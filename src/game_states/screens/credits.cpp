#include "credits.h"

#include "general/game.h"

namespace game
{
Credits::Credits()
{
	text.resize(CREDITS_TEXT_ROWS_AMOUNT);
	for (int i = 0; i < CREDITS_TEXT_ROWS_AMOUNT; i++)
	{
		text[i] = NULL;
	}

	text[18] = new DisplayText("v1.0", false, 0.0f, Color::Red, PARAGRAPH_FONT_SIZE);
	text[17] = new DisplayText("Press 'Enter' to return to menu", false, SCREEN_HEIGHT - CREDITS_TEXT_SPACING, Color::Yellow, PARAGRAPH_FONT_SIZE);
	text[16] = new DisplayText("Microsoft Visual Studio 2017 (visualstudio.microsoft.com)", true, CREDITS_INTIAL_POS, Color::White, PARAGRAPH_FONT_SIZE);
	text[15] = new DisplayText("IDE", true, text[16]->getUpperSide() - CREDITS_TEXT_SPACING, Color::White, PARAGRAPH_FONT_SIZE);
	text[14] = new DisplayText("Audacity 2.3.3 (audacityteam.org)", true, text[15]->getUpperSide() - CREDITS_TEXT_SPACING *2, Color::White, PARAGRAPH_FONT_SIZE);
	text[13] = new DisplayText("Audio Editing", true, text[14]->getUpperSide() - CREDITS_TEXT_SPACING, Color::White, PARAGRAPH_FONT_SIZE);
	text[12] = new DisplayText("Adobe Photoshop CC 2019 (photoshop.com)", true, text[13]->getUpperSide() - CREDITS_TEXT_SPACING * 2, Color::White, PARAGRAPH_FONT_SIZE);
	text[11] = new DisplayText("Image Editing", true, text[12]->getUpperSide() - CREDITS_TEXT_SPACING, Color::White, PARAGRAPH_FONT_SIZE);
	text[10] = new DisplayText("Kenney (kenney.nl)", true, text[11]->getUpperSide() - CREDITS_TEXT_SPACING * 2, Color::White, PARAGRAPH_FONT_SIZE);
	text[9] = new DisplayText("All Visual & Audio Assets", true, text[10]->getUpperSide() - CREDITS_TEXT_SPACING, Color::White, PARAGRAPH_FONT_SIZE);
	text[8] = new DisplayText("SFML (sfml-dev.org)", true, text[9]->getUpperSide() - CREDITS_TEXT_SPACING * 2, Color::White, PARAGRAPH_FONT_SIZE);
	text[7] = new DisplayText("Engine", true, text[8]->getUpperSide() - CREDITS_TEXT_SPACING, Color::White, PARAGRAPH_FONT_SIZE);
	text[6] = new DisplayText("Sani (Instagram: @sani_draws)", true, text[7]->getUpperSide() - CREDITS_TEXT_SPACING * 2, Color::White, PARAGRAPH_FONT_SIZE);
	text[5] = new DisplayText("Interface Music - resamebeleing", true, text[6]->getUpperSide() - CREDITS_TEXT_SPACING, Color::White, PARAGRAPH_FONT_SIZE);
	text[4] = new DisplayText("Micael \"BlueEagle\" Lucuman (soundcloud.com/blueeagle98)", true ,text[5]->getUpperSide() - CREDITS_TEXT_SPACING * 2, Color::White, PARAGRAPH_FONT_SIZE);
	text[3] = new DisplayText("Gameplay Music - Friendly Fire", true, text[4]->getUpperSide() - CREDITS_TEXT_SPACING, Color::White, PARAGRAPH_FONT_SIZE);
	text[2] = new DisplayText("Lucio Ruixo & Iñaki Diez Galarza", true, text[3]->getUpperSide() - CREDITS_TEXT_SPACING * 2, Color::White, PARAGRAPH_FONT_SIZE);
	text[1] = new DisplayText("Game Programing + Developing", true, text[2]->getUpperSide() - CREDITS_TEXT_SPACING, Color::White, PARAGRAPH_FONT_SIZE);
	text[0] = new DisplayText("CREDITS", false, CREDITS_TEXT_SPACING/2, Color::Yellow, PARAGRAPH_FONT_SIZE);

	text[18]->setPosition(VERSION_TEXT_POS);
}

Credits::~Credits()
{
}

void Credits::checkKeyDownInput()
{
	Game::window->setKeyRepeatEnabled(false);

	if (Keyboard::isKeyPressed(Keyboard::Enter))
	{
		if (!Game::getGameStateInputActive())
		{
			if (!Game::getAudioMuted())
			{
				Game::buttonSFX.play();
			}
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
		if (text[i]) text[i]->setPositionY(text[i]->getInitialPos().y);
	}
}

void Credits::scroll()
{
	for (int i = 0; i < CREDITS_TEXT_ROWS_AMOUNT; i++)
	{
		if (text[i])
		{
			if (text[i]->getCentered() == true)
			{
				if (text[CREDITS_TEXT_ROWS_AMOUNT-3]->getBottomSide()<0)
				{
					setInitialPos();
					break;
				}
				text[i]->setPositionY(text[i]->getUpperSide()-TEXT_SCROLLING_SPEED*Game::deltaTime);
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
	drawText();
}
}