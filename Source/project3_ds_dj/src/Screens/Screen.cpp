#include "Screens\Screen.h"

/// <summary>
/// Screen constructor function
/// </summary>
/// <param name="gameStateIn">The game state assigned to the screen</param>
Screen::Screen(GameState gameStateIn, sf::View &view)
	: m_gameState(gameStateIn), m_nextGameState(gameStateIn), m_view(view)
{

}

/// <summary>
/// 
/// </summary>
void Screen::reset()
{

}

void Screen::update(XboxController & controller, sf::Int32 dt)
{

}

/// <summary>
/// Function draws the gui object
/// </summary>
/// <param name="renderTexture">The render texture used to draw the game</param>
void Screen::render(sf::RenderTexture& renderTexture)
{
	renderTexture.setView(m_view);
	renderTexture.draw(m_gui);
}

/// <summary>
/// Getter function for the game state of the screen
/// </summary>
/// <returns>The game state of the screen</returns>
GameState Screen::getGameState()
{
	return m_gameState;
}

/// <summary>
/// Getter function for the nextGameState member
/// </summary>
/// <returns>The next game state for the screen manager to update</returns>
GameState Screen::getNextGameState()
{
	return m_nextGameState;
}

/// <summary>
/// Function used to reset the next game state for the screen
/// </summary>
void Screen::resetNextGameState()
{
	m_nextGameState = m_gameState;
	// Reset this screen so it will be ready to run from the start again
	reset();
}