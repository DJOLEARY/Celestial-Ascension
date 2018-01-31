#include "Screens\Leaderboard.h"

Leaderboard::Leaderboard(sf::View &view)
	: Screen(GameState::Leaderboard, view), m_transitionIn(true)
{
	// 1. Create a leaderboard file if one does not exsist

	// 2. Populate the leaderboad with default data

	// 3. Get gui to display leaderboard

	sf::Color focusIn(50, 200, 50);
	sf::Color focusOut(100, 20, 50);

	m_leaderboardTitle = new Label("Leaderboard", 80, sf::Vector2f(1920.0f / 2 - 400.0f, 120.0f),
														sf::Vector2f(1920.0f / 2, 120.0f));

	for (int i = 0; i < 10; i++)
	{
		m_numbers[i] = new Label(std::to_string(i + 1), 30, sf::Vector2f(1920.0f / 2 - 300, (70.0f * i) + 230),
			sf::Vector2f(1920.0f / 2 + 100, (70.0f * i) + 230));

		m_names[i] = new Label("DAR", 30, sf::Vector2f(1920.0f / 2, (70.0f * i) + 230),
			sf::Vector2f(1920.0f / 2 + 400, (70.0f * i) + 230));

		m_scores[i] = new Label("42030", 30, sf::Vector2f(1920.0f / 2 + 300, (70.0f * i) + 230),
			sf::Vector2f(1920.0f / 2 + 700, (70.0f * i) + 230));
	}

	m_backTexure.loadFromFile("Assets/GUI/BackButton.png");
	m_backButton = new Button(m_backTexure, sf::Vector2f(1920.0f / 2, 950.0f), focusIn, focusOut,
		1.0f, 1.0f, sf::Vector2f(1920.0f / 2 + 400.0f, 950.0f));
	m_backButton->select = std::bind(&Leaderboard::backButtonSelected, this);
	m_backButton->promoteFocus();

	m_gui.add(m_leaderboardTitle);
	for (int i = 0; i < 10; i++)
	{
		m_gui.add(m_numbers[i]);
		m_gui.add(m_names[i]);
		m_gui.add(m_scores[i]);
	}
	m_gui.add(m_backButton);

	m_gui.setWidgetsAlpha(0.0f);
}

void Leaderboard::update(XboxController &controller, sf::Int32 dt)
{
	m_gui.processInput(controller);

	if (controller.isButtonPressed(XBOX360_B))
	{
		m_backButtonPressed = true;
	}

	if (m_backButtonPressed)
	{
		m_gui.transitionOut(0.05f, m_interpolation);

		if (m_interpolation >= 1.0f)
		{
			m_nextGameState = GameState::PlayMenu;
			reset();
		}
	}

	if (m_transitionIn)
	{
		m_gui.transitionIn(0.05f, m_interpolation);

		if (m_interpolation >= 1.0f)
		{
			m_interpolation = 0.0f;
			m_transitionIn = false;
		}
	}
}

void Leaderboard::reset()
{
	m_transitionIn = true;
	m_interpolation = 0.0f;
	m_backButtonPressed = false;
}

void Leaderboard::backButtonSelected()
{
	m_backButtonPressed = true;
}