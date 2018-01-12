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

	void update(XboxController &controller, sf::Int32 dt);
	void draw(sf::RenderTexture &renderTexture);
	void add(Screen *Screen);

private:
	std::vector<Screen *> m_screens;
	GameState m_gameState;
	uint8_t m_currentScreen;
	sf::Clock m_clock;
};

#endif