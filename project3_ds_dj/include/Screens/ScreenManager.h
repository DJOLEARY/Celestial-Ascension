/// <summary>
/// @author Darren Sweeney
/// </summary>

#ifndef  SCRENMANAGER_H
#define SCREENMANAGER_H

#include "Screen.h"

class ScreenManager
{
public:
	ScreenManager();
	~ScreenManager();

	void update(XboxController &controller);
	void draw(sf::RenderTexture &renderTexture);
	void add(Screen *Screen);

private:
	std::vector<Screen *> m_screens;
	GameState m_gameState;
	uint8_t m_currentScreen;
};

#endif