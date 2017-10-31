#include "Screens\Credits.h"

Credits::Credits()
	: Screen(GameState::Credits), transitionIn(true)
{
	m_creditsLabel = new Label("Credits", 80, sf::Vector2f(1920.0f / 2 - 400.0f, 100.0f), 
		sf::Vector2f(1920.0f / 2, 100.0f));

	m_names[0] = new Label("Darren Sweeney", 30, sf::Vector2f(1920.0f / 2 - 400.0f, 600.0f),
		sf::Vector2f(1920.0f / 2 - 400.0f, 800.0f));
	m_names[1] = new Label("D.J O' Leary", 30, sf::Vector2f(1920.0f / 2 + 400.0f, 600.0f),
		sf::Vector2f(1920.0f / 2 + 400.0f, 800.0f));
	m_names[2] = new Label("Project Supervison : Philip Burke", 30, sf::Vector2f(1920.0f / 2, 700.0f),
		sf::Vector2f(1920.0f / 2, 900.0f));

	m_gui.add(m_creditsLabel);
	for (uint8_t i = 0; i < 3; i++)
		m_gui.add(m_names[i]);

	m_gui.setWidgetsAlpha(0.0f);
}

// @refactor(darren): Could i refactor this into base scene?
void Credits::update(XboxController& controller)
{
	m_gui.processInput(controller);

	if (controller.isButtonPressed(XBOX360_B))
	{
		m_backButtonPressed = true;
	}

	if (m_backButtonPressed)
	{
		m_gui.transitionOut(0.05f, interpolation);

		if (interpolation >= 1.0f)
		{
			m_nextGameState = GameState::MainMenu;
			reset();
		}
	}

	if (transitionIn)
	{
		m_gui.transitionIn(0.05f, interpolation);

		if (interpolation >= 1.0f)
		{
			interpolation = 0.0f;
			transitionIn = false;
		}
	}
}

void Credits::reset()
{
	m_backButtonPressed = false;
	transitionIn = true;
	interpolation = 0.0f;
}