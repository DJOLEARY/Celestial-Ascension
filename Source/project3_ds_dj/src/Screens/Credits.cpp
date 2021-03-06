#include "Screens\Credits.h"

Credits::Credits(sf::View &view, sf::Sound *backSound)
	: Screen(GameState::Credits, view), transitionIn(true), m_backSound(backSound)
{
	m_creditsLabel = new Label("Credits", 80, sf::Vector2f(1920.0f / 2 - 300.0f, 200.0f), 
		sf::Vector2f(1920.0f / 2, 200.0f));

	m_text[0] = new Label("Darren Sweeney", 30, sf::Vector2f(1920.0f / 2 - 400.0f, 500.0f),
		sf::Vector2f(1920.0f / 2 - 400.0f, 700.0f));
	m_text[1] = new Label("darrensweeney.net", 30, sf::Vector2f(1920.0f / 2 - 400.0f, 550.0f),
		sf::Vector2f(1920.0f / 2 - 400.0f, 750.0f));
	m_text[2] = new Label("D.J O' Leary", 30, sf::Vector2f(1920.0f / 2 + 400.0f, 500.0f),
		sf::Vector2f(1920.0f / 2 + 400.0f, 700.0f));
	m_text[3] = new Label("Project Supervison : Philip Burke", 30, sf::Vector2f(1920.0f / 2, 700.0f),
		sf::Vector2f(1920.0f / 2, 900.0f));

	m_gui.add(m_creditsLabel);
	for (uint8_t i = 0; i < 4; i++)
		m_gui.add(m_text[i]);

	m_gui.setWidgetsAlpha(0.0f);
}

// @refactor(darren): Could i refactor this into base scene?
void Credits::update(XboxController& controller, sf::Int32 dt)
{
	m_gui.processInput(controller);

	if (controller.isButtonPressed(XBOX360_B))
	{
		m_backButtonPressed = true;
		m_backSound->play();
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