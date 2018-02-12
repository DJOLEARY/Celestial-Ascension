#include "Screens\ExitMenu.h"

ExitMenu::ExitMenu(sf::View &view, sf::Sound *confirmSound, sf::Sound *navigateSound) :
	Screen(GameState::ExitMenu, view), 
	transitionIn(true),
	m_confirmSound(confirmSound),
	m_navigateSound(navigateSound)
{
	// @refactor(darren): Move this into scene manager and have all scens uses the same colors
	sf::Color focusIn(50, 200, 50);
	sf::Color focusOut(100, 20, 50);

	if (!m_yesTexture.loadFromFile("Assets/GUI/YesButton.png"))
		std::cout << "ERROR::Options::Yes Texture image not loaded";

	if (!m_noTexture.loadFromFile("Assets/GUI/NoButton.png"))
		std::cout << "ERROR::Options::No Texture image not loaded";

	m_exitGameLabel = new Label("Exit", 80, sf::Vector2f(1920.0f / 2 - 400.0f, 200.0f), sf::Vector2f(1920.0f / 2, 200.0f));
	m_areYouSureLabel = new Label("Are you sure?", 60, sf::Vector2f(1920.0f / 2, 450.0f), sf::Vector2f(1920.0f / 2 + 400.0f, 450.0f));
	m_noButton = new Button(m_confirmSound, m_navigateSound, m_noTexture, sf::Vector2f(1920.0f / 2 - 150.0f, 550.0f), focusIn, focusOut, 0.75f, 0.75f, sf::Vector2f(1920.0f / 2 - 150.0f, 650.0f));
	m_yesButton = new Button(m_confirmSound, m_navigateSound, m_yesTexture, sf::Vector2f(1920.0f / 2 + 150.0f, 550.0f), focusIn, focusOut, 0.75f, 0.75f, sf::Vector2f(1920.0f / 2 + 150.0f, 650.0f));

	m_noButton->select = std::bind(&ExitMenu::noButtonSelected, this);
	m_yesButton->select = std::bind(&ExitMenu::yesButtonSelected, this);

	m_noButton->promoteFocus();

	m_noButton->m_right = m_yesButton;
	m_yesButton->m_left = m_noButton;

	m_gui.add(m_exitGameLabel);
	m_gui.add(m_areYouSureLabel);
	m_gui.add(m_yesButton);
	m_gui.add(m_noButton);

	m_gui.setWidgetsAlpha(0.0f);
}

void ExitMenu::reset()
{
	m_noButton->promoteFocus();
	m_yesButton->demoteFocus();
	m_noButtonPressed = false;
	m_yesButtonPressed = false;
	transitionIn = true;
	interpolation = 0.0f;
}

bool ExitMenu::getExitState()
{
	return m_yesButtonPressed;
}

void ExitMenu::update(XboxController &controller, sf::Int32 dt)
{
	if (controller.isButtonPressed(XBOX360_B))
	{
		m_noButtonPressed = true;
	}

	if (m_noButtonPressed)
	{
		m_gui.transitionOut(0.05f, interpolation);

		if (interpolation >= 1.0f)
		{
			m_nextGameState = GameState::MainMenu;
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

void ExitMenu::yesButtonSelected()
{
	m_yesButtonPressed = true;
	m_confirmSound->play();
}

void ExitMenu::noButtonSelected()
{
	m_noButtonPressed = true;
	m_confirmSound->play();
}