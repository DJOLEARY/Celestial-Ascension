#include "Screens\ScreenManager.h"
#include "Physics\Grid.h"
#include "Physics\ParticleManager.h"

ScreenManager::ScreenManager()
	: m_gameState(GameState::SplashScreen), m_currentScreen(0)
{
	
}

ScreenManager::~ScreenManager()
{
	for (Screen *screen : m_screens)
		delete screen;
}

/// <summary>
/// update function updtes the current screen based off of the current game state
/// </summary>
/// <param name="controller">The controller to be passed to each screen when updating</param>
void ScreenManager::update(XboxController &controller, sf::Int32 dt)
{
	// We use the variable m_currentScreen so as we don't have to loop through the vector again when rendering
	for (m_currentScreen = 0; m_currentScreen < m_screens.size(); m_currentScreen++)
	{
		if (m_screens.at(m_currentScreen)->getGameState() == m_gameState) // Check if the game state of the screen matches the current game state
		{
            if (m_gameState != GameState::GamePlay)
            {
                m_screens.at(m_currentScreen)->update(controller); // Update the current screen

				sf::Time elapsedTime = m_clock.getElapsedTime();
				if (elapsedTime.asSeconds() > 2)
				{
					sf::Vector2f position(sf::randF(100.0f, 1800.0f), sf::randF(100.0f, 1000.0f));
					ParticleManager::instance()->createExplosion(position, sf::Color(216, 114, 30));
					Grid::instance()->applyImplosiveForce(50.0f, sf::Vector3f(position.x, position.y, -20.0f), 100.0f);
					m_clock.restart();
				}
            }
            else
            {
                m_screens.at(m_currentScreen)->update(controller, dt); // Update the the game screen.
            }

			GameState nextState = m_screens.at(m_currentScreen)->getNextGameState();
			if (nextState != m_gameState) // Check if the screen wants to switch game states
			{
				if (GameState::Options == m_gameState)
				{
					for (Screen *screen : m_screens)
					{
						if (screen->getGameState() == GameState::GamePlay)
						{
							screen->reset(); // We need to also reset the game if this is the case
						}
					}
				}
				m_gameState = nextState; // Set the current game state
				m_screens.at(m_currentScreen)->resetNextGameState(); // Reset the game state of the net screen member of the current screen
			}
			break; 
		}
	}
}

/// <summary>
/// render function draws the current screen which is decided in the update function
/// </summary>
/// <param name="renderTexture">The render texture used for drawing the screens</param>
void ScreenManager::draw(sf::RenderTexture &renderTexture)
{
	if (m_currentScreen < m_screens.size())
		m_screens.at(m_currentScreen)->render(renderTexture);
}
/// <summary>
/// add function used to add a pointer to a screen onto the screen manager object
/// </summary>
/// <param name="screenIn">A pointer to a screen declared on the heap</param>
void ScreenManager::add(Screen *screenIn)
{
	m_screens.push_back(screenIn);
}