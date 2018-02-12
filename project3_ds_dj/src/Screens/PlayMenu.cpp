#include "Screens\PlayMenu.h"

PlayMenu::PlayMenu(sf::View &view, sf::Sound *confirmSound, sf::Sound *m_navigateSound) :
	Screen(GameState::PlayMenu, view), 
	transitionIn(true),
	m_confirmSound(confirmSound)
{
	// @refactor(darren): Pull this out
	sf::Color focusIn(50, 200, 50);
	sf::Color focusOut(100, 20, 50);

	if (!m_playTexture.loadFromFile("Assets/GUI/BattleIcon.png"))
		std::cout << "ERROR::PlayMenu::BattleIcon image not loaded";

	if (!m_leaderboardTexture.loadFromFile("Assets/GUI/leaderboard_icon.png"))
		std::cout << "ERROR::PlayMenu::upgrade_icon image not loaded";

	m_playButton = new Button(m_confirmSound, m_navigateSound, m_playTexture, sf::Vector2f(1920.0f / 2 - 300.0f, 500.0f), focusIn, focusOut, 
		0.75f, 0.75f, sf::Vector2f(1920.0f / 2 - 500.0f, 500));
	m_leaderboardButton = new Button(m_confirmSound, m_navigateSound, m_leaderboardTexture, sf::Vector2f(1920.0f / 2 + 300.0f, 500.0f), focusIn, focusOut,
		0.75f, 0.75f, sf::Vector2f(1920.0f / 2 + 500.0f, 500));

	m_playButton->select = std::bind(&PlayMenu::playButtonSelected, this);
	m_leaderboardButton->select = std::bind(&PlayMenu::leaderboardButtonSelected, this);

	m_playButton->promoteFocus();

	m_playButton->m_right = m_leaderboardButton;
	m_leaderboardButton->m_left = m_playButton;

	m_gui.add(m_playButton);
	m_gui.add(m_leaderboardButton);

	m_gui.setWidgetsAlpha(0.0f);
}

void PlayMenu::update(XboxController &controller, sf::Int32 dt)
{
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
	else if (m_playButtonPressed)
	{
		m_gui.transitionOut(0.05f, interpolation);

		if (interpolation >= 1.0f)
		{
			m_nextGameState = GameState::GamePlay;
			m_playButton->promoteFocus();
			m_leaderboardButton->demoteFocus();
			reset();
		}
	}
	else if (m_leaderboardButtonPressed)
	{
		m_gui.transitionOut(0.05f, interpolation);

		if (interpolation >= 1.0f)
		{
			m_nextGameState = GameState::Leaderboard;
			m_playButton->demoteFocus();
			m_leaderboardButton->promoteFocus();
			reset();
		}
	}
	else
		m_gui.processInput(controller);

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

void PlayMenu::reset()
{
	m_playButtonPressed = false;
	m_leaderboardButtonPressed = false;
	m_backButtonPressed = false;
	transitionIn = true;
	interpolation = 0.0f;
}

void PlayMenu::playButtonSelected()
{
	m_playButtonPressed = true;
}

void PlayMenu::leaderboardButtonSelected()
{
	m_leaderboardButtonPressed = true;
}