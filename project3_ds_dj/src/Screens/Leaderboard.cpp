#include "Screens\Leaderboard.h"
#include <fstream>

Leaderboard::Leaderboard(sf::View &view)
	: Screen(GameState::Leaderboard, view), m_transitionIn(true)
{
	// @todo(darren): If file does not exsist then create it
	const char *names[10] = {"DAR", "LIZ", "JHN", "BOB", "XOX", "JOE", "AMY", "POP", "JAN", "WOZ" };
	std::ofstream outputLeaderboardFile;
	outputLeaderboardFile.open("leaderboard.txt");
	if (outputLeaderboardFile.is_open())
	{
		for (int i = 0; i < 10; i++)
		{
			outputLeaderboardFile << names[i] << " " << 22400 - (i * 500) << "\n";
		}
	}
	outputLeaderboardFile.close();

	std::ifstream inputLeaderboardFile;
	inputLeaderboardFile.open("leaderboard.txt");
	if (inputLeaderboardFile.is_open())
	{
		for (int i = 0; i < 10; i++)
		{
			inputLeaderboardFile >> m_readInNames[i] >> m_readInScores[i];
		}
	}
	inputLeaderboardFile.close();
	
	sf::Color focusIn(50, 200, 50);
	sf::Color focusOut(100, 20, 50);

	m_leaderboardTitle = new Label("Leaderboard", 80, sf::Vector2f(1920.0f / 2 - 400.0f, 120.0f),
														sf::Vector2f(1920.0f / 2, 120.0f));

	for (int i = 0; i < 10; i++)
	{
		m_numbers[i] = new Label(std::to_string(i + 1), 30, sf::Vector2f(1920.0f / 2 - 300, (70.0f * i) + 230),
			sf::Vector2f(1920.0f / 2 + 100, (70.0f * i) + 230));

		m_names[i] = new Label(m_readInNames[i], 30, sf::Vector2f(1920.0f / 2, (70.0f * i) + 230),
			sf::Vector2f(1920.0f / 2 + 400, (70.0f * i) + 230));

		m_scores[i] = new Label(std::to_string(m_readInScores[i]), 30, sf::Vector2f(1920.0f / 2 + 300, (70.0f * i) + 230),
			sf::Vector2f(1920.0f / 2 + 700, (70.0f * i) + 230));
	}

	m_gui.add(m_leaderboardTitle);
	for (int i = 0; i < 10; i++)
	{
		m_gui.add(m_numbers[i]);
		m_gui.add(m_names[i]);
		m_gui.add(m_scores[i]);
	}

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