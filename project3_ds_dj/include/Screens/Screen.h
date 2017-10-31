/// <summary>
/// @author Darren Sweeney
/// </summary>

#ifndef SCREEN_H
#define SCREEN_H

#include <SFML\Graphics.hpp>
#include "XboxController.h"	
#include "GUI\GUI.h"

/// <summary>
/// Define the gamestate here as it is accessible to everything that neds it at this point
/// as all screens have a GameSate and the ScreenManager has a GameState
/// </summary>
enum class GameState
{
	SplashScreen,
	MainMenu,
	Options,
	ExitMenu,
	Credits,
	PlayMenu,
	GamePlay
};

/// <summary>
/// Brief: General screen class inherited by all objects of type screen
///
/// Detail: Handles general functionality of the in game screens like drawing etc
/// </summary>
class Screen
{
public:
	Screen(GameState gameStateIn);
	virtual void reset();
	virtual void update(XboxController& controller) = 0;
	virtual void render(sf::RenderWindow& window);
	GameState getGameState();
	GameState getNextGameState();
	void resetNextGameState();

protected:
	// GameState variables
	GameState m_gameState;
	GameState m_nextGameState;

	// GUI object
	Gui m_gui;
};

#endif
