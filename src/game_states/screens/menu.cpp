#include "menu.h"

#include "general/game.h"

namespace game
{
Menu::Menu()
{
	muteButtonPressed = false;

	text.resize(MENU_TEXT_ROWS_AMOUNT);

	for (int i = 0; i < MENU_TEXT_ROWS_AMOUNT; i++)
	{
		text[i] = NULL;
	}

	text[0] = new DisplayText("Press 'Enter' to play", true, LOGO_POSITION_Y + MENU_LOGO_SPACING, Color::White, PARAGRAPH_FONT_SIZE);
	text[1] = new DisplayText("Press 'C' to see the credits", true, text[0]->getUpperSide() + MENU_PARAGRAPH_SPACING, Color::White, PARAGRAPH_FONT_SIZE);
	text[2] = new DisplayText("Press 'M' to mute/unmute music", true, text[1]->getUpperSide() + MENU_PARAGRAPH_SPACING, Color::White, PARAGRAPH_FONT_SIZE);
	text[3] = new DisplayText("Press 'Escape' to exit", true, text[2]->getUpperSide() + MENU_PARAGRAPH_SPACING, Color::White, PARAGRAPH_FONT_SIZE);
	text[4] = new DisplayText("v1.1", true, 0.0f, Color::Red, PARAGRAPH_FONT_SIZE);
	
	text[4]->setPosition(VERSION_TEXT_POS);

	logoTexture.loadFromFile("images/logo.png");
	logoTextureRect = new IntRect(0, 0, logoTexture.getSize().x, logoTexture.getSize().y);
	logoSprite.setTexture(logoTexture);
	logoSprite.setTextureRect(*logoTextureRect);
	logoSprite.setPosition((SCREEN_WIDTH - logoTextureRect->width) / 2.0f, LOGO_POSITION_Y);

	if (Game::interfaceMusic.getStatus()!= Music::Playing) Game::interfaceMusic.play();
}

Menu::~Menu()
{
	if (Game::currentGameState==gameplay_state) Game::interfaceMusic.stop();
}

void Menu::checkKeyDownInput()
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
			Game::currentGameState=gameplay_state;
		}
	}
	else
	{
		if (Game::getGameStateInputActive())
		{
			Game::setGameStateInputActive(false);
		}
	}

	if (Keyboard::isKeyPressed(Keyboard::C))
	{
		if (!Game::getAudioMuted())
		{
			Game::buttonSFX.play();
		}
		Game::currentGameState=credits_state;
	}

	if (Keyboard::isKeyPressed(Keyboard::Escape))
	{
		if (!Game::getAudioMuted())
		{
			Game::buttonSFX.play();
		}
		Game::window->close();
	}

	if (!muteButtonPressed)
	{
		if (Keyboard::isKeyPressed(Keyboard::M))
		{
			Game::buttonSFX.play();
			Game::setAudioMuted(!Game::getAudioMuted());
			muteButtonPressed = true;
		}
	}
	else
	{
		if (!Keyboard::isKeyPressed(Keyboard::M))
		{
			muteButtonPressed = false;
		}
	}


	Game::window->setKeyRepeatEnabled(true);
}

void Menu::update()
{
	checkKeyDownInput();
}

void Menu::draw()
{
	Game::window->draw(logoSprite);
	drawText();
}
}