#include "Screens\ScreenManager.h"
#include "Physics\Grid.h"
#include "Physics\ParticleManager.h"

ScreenManager::ScreenManager()
	: m_gameState(GameState::SplashScreen), m_currentScreen(0)
{
	m_xboxButtonTexture.loadFromFile("Assets/Xbox_Controller_Buttons.png");
	m_xboxLeftStick.setTexture(m_xboxButtonTexture);
	m_xboxLeftStick.setTextureRect(sf::IntRect(0, 0, 80, 90));
	m_xboxLeftStick.setPosition(sf::Vector2f(75.0f, 910.0f));

	m_xboxArrowButton.setTexture(m_xboxButtonTexture);
	m_xboxArrowButton.setTextureRect(sf::IntRect(80, 0, 80, 90));
	m_xboxArrowButton.setPosition(sf::Vector2f(175.0f, 910.0f));

	m_xboxButtonA.setTexture(m_xboxButtonTexture);
	m_xboxButtonA.setTextureRect(sf::IntRect(160, 0, 80, 90));
	m_xboxButtonA.setPosition(sf::Vector2f(1615.0f, 910.0f));

	m_xboxButtonB.setTexture(m_xboxButtonTexture);
	m_xboxButtonB.setTextureRect(sf::IntRect(240, 0, 90, 90));
	m_xboxButtonB.setPosition(sf::Vector2f(1760.0f, 910.0f));

	m_font.loadFromFile("Assets/Fonts/OCRAEXT.TTF");
	m_buttonUIText.setFont(m_font);
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
	if (m_gameState != GameState::GamePlay)
	{
		renderTexture.draw(m_xboxLeftStick);
		renderTexture.draw(m_xboxArrowButton);
		m_buttonUIText.setPosition(sf::Vector2f(95.0f, 975.0f));
		m_buttonUIText.setString("Navigate");
		renderTexture.draw(m_buttonUIText);

		renderTexture.draw(m_xboxButtonA);
		m_buttonUIText.setPosition(sf::Vector2f(1600.0f, 975.0f));
		m_buttonUIText.setString("Select");
		renderTexture.draw(m_buttonUIText);

		renderTexture.draw(m_xboxButtonB);
		m_buttonUIText.setPosition(sf::Vector2f(1755.0f, 975.0f));
		m_buttonUIText.setString("Back");
		renderTexture.draw(m_buttonUIText);
	}

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