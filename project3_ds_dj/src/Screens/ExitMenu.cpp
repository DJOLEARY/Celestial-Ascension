#include "Screens\ExitMenu.h"

ExitMenu::ExitMenu()
	: Screen(GameState::ExitMenu)
{
	// @refactor(darren): Move this into scene manager and have all scens uses the same colors
	sf::Color focusIn(255, 0, 0);
	sf::Color focusOut(0, 255, 0);
	sf::Color fillColor(0, 0, 255);

	if (!m_yesTexture.loadFromFile("Assets/GUI/ApplyButton.png"))
		std::cout << "ERROR::Options::Yes Texture image not loaded";

	if (!m_noTexture.loadFromFile("Assets/GUI/ApplyButton.png"))
		std::cout << "ERROR::Options::No Texture image not loaded";

	m_exitGameLabel = new Label("Exit", 80, sf::Vector2f(1920.0f / 2 - 400.0f, 100.0f), sf::Vector2f(1920.0f / 2, 100.0f));
	m_areYouSureLabel = new Label("Are you sure?", 60, sf::Vector2f(1920.0f / 2, 450.0f), sf::Vector2f(1920.0f / 2 + 400.0f, 450.0f));
	m_yesButton = new Button(m_yesTexture, sf::Vector2f(1920.0f / 2 - 150.0f, 550.0f), focusIn, focusOut, 1.0f, 1.0f, sf::Vector2f(1920.0f / 2 - 150.0f, 650.0f));
	m_noButton = new Button(m_noTexture, sf::Vector2f(1920.0f / 2 + 150.0f, 550.0f), focusIn, focusOut, 1.0f, 1.0f, sf::Vector2f(1920.0f / 2 + 150.0f, 650.0f));

	m_noButton->promoteFocus();

	m_noButton->m_right = m_yesButton;
	m_yesButton->m_left = m_noButton;

	m_gui.add(m_exitGameLabel);
	m_gui.add(m_areYouSureLabel);
	m_gui.add(m_yesButton);
	m_gui.add(m_noButton);

	//m_gui.setWidgetsAlpha(0.0f);
}

void ExitMenu::update(XboxController &controller)
{
	m_gui.processInput(controller);

	if (controller.isButtonPressed(XBOX360_BACK))
	{
		m_noButtonPressed = true;
	}

	if (m_noButtonPressed)
	{
		m_gui.transitionOut(0.05f, interpolation);

		if (interpolation >= 1.0f)
		{
			m_nextGameState = GameState::MainMenu;
			interpolation = 0.0f;
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

void ExitMenu::reset()
{
	m_noButton->promoteFocus();
	transitionIn = true;
	interpolation = 0.0f;
	m_noButtonPressed = false;
}

void ExitMenu::yesButtonSelected()
{

}

void ExitMenu::noButtonSelected()
{
	m_noButtonPressed = true;
}