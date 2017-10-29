#include "Screens\MainMenu.h"

MainMenu::MainMenu()
	: Screen(GameState::MainMenu), m_alphaFadeValue(0)
{
	m_fadeRectangle.setSize(sf::Vector2f(800.0f, 800.0f));
	m_fadeRectangle.setFillColor(sf::Color(0.0f, 0.0f, 0.0f, m_alphaFadeValue));

	m_gameTitle = new Label("This is a label", 24, sf::Vector2f(1920 / 2, 150.0f), sf::Vector2f(1500.0f, 150.0f));

	if (!buttonOneTexture.loadFromFile("Assets/PlayButton.png"))
		std::cout << "ERROR::Player::Image not loaded";

	if (!buttonTwoTexture.loadFromFile("Assets/ExitButton.png"))
		std::cout << "ERROR::Player::Image not loaded";

	// @todo(darren): Take in the screen resolution so i can allign things correctly
	m_playButton = new Button(buttonOneTexture, sf::Vector2f(1920 / 2, 300.0f),
		sf::Color(205, 20, 50), sf::Color(20, 40, 105), 1.0f, 1.0f, sf::Vector2f(1920.0f / 2 + 400.0f, 300.0f));
	m_optionsButton = new Button(buttonTwoTexture, sf::Vector2f(1920 / 2, 450.0f),
		sf::Color(205, 20, 50), sf::Color(20, 40, 105), 1.0f, 1.0f, sf::Vector2f(1920.0f / 2 + 400.0f, 450.0f));
	m_creditsButton = new Button(buttonTwoTexture, sf::Vector2f(1920 / 2, 600.0f),
		sf::Color(205, 20, 50), sf::Color(20, 40, 105), 1.0f, 1.0f, sf::Vector2f(1920.0f / 2 + 400.0f, 600.0f));
	m_exitButton = new Button(buttonTwoTexture, sf::Vector2f(1920 / 2, 750.0f),
		sf::Color(205, 20, 50), sf::Color(20, 40, 105), 1.0f, 1.0f, sf::Vector2f(1920.0f / 2 + 400.0f, 750.0f));

	m_playButton->select = std::bind(&MainMenu::playButtonSelected, this);
	m_optionsButton->select = std::bind(&MainMenu::optionsButtonSelected, this);
	m_creditsButton->select = std::bind(&MainMenu::creditsButtonSelected, this);
	m_exitButton->select = std::bind(&MainMenu::quitButtonSelected, this);

	m_playButton->promoteFocus();

	m_playButton->m_down = m_optionsButton;
	m_optionsButton->m_up = m_playButton;
	m_optionsButton->m_down = m_creditsButton;
	m_creditsButton->m_up = m_optionsButton;
	m_creditsButton->m_down = m_exitButton;
	m_exitButton->m_up = m_creditsButton;

	m_gui.add(m_gameTitle);
	m_gui.add(m_playButton);
	m_gui.add(m_optionsButton);
	m_gui.add(m_creditsButton);
	m_gui.add(m_exitButton);
}

/// <summary>
/// Reset function used to reset the main menu after the game state has been changed
/// </summary>
void MainMenu::reset()
{
	optionsButtonPressed = false;
	exitButtonPressed = false;
	playButtonPressed = false;
	transitionIn = true;
	interpolation = 0.0f;
}

/// <summary>
/// update function updates the main menu and its GUI
/// </summary>
/// <param name="controller">Controller used for processing input</param>
void MainMenu::update(XboxController &controller)
{
	m_fadeRectangle.setFillColor(sf::Color(0.0f, 0.0f, 0.0f, m_alphaFadeValue)); 
	if (m_alphaFadeValue >= FADE_RATE)
	{
		m_alphaFadeValue -= FADE_RATE;
	}

	m_gui.processInput(controller);

	if (playButtonPressed)
	{
		m_gui.transitionOut(0.05f, interpolation); 
		if (interpolation >= 1.0f)
		{
			m_nextGameState = GameState::GamePlay; 
			interpolation = 0.0f; // Reset the interpolation
			reset(); // Reset the main menu
		}
	}
	else if (optionsButtonPressed) 
	{
		m_gui.transitionOut(0.05f, interpolation);
		if (interpolation >= 1.0f)
		{
			m_nextGameState = GameState::Options;
			interpolation = 0.0f;
			reset();
		}
	}
	else if (creditsButtonsPressed)
	{
		m_gui.transitionOut(0.05f, interpolation);
		if (interpolation >= 1.0f)
		{
			m_nextGameState = GameState::Credits;
			interpolation = 0.0f;
			reset();
		}
	}
	else if (exitButtonPressed)
	{
		m_gui.transitionOut(0.05f, interpolation);
		if (interpolation >= 1.0f)
		{
			m_nextGameState = GameState::ExitMenu;
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

/// <summary>
/// Render function used to draw the main menu and its GUI
/// </summary>
/// <param name="window">window usd to render the GUI and fade rectangle</param>
void MainMenu::render(sf::RenderWindow & window)
{
	window.draw(m_fadeRectangle);
	window.draw(m_gui);
}

/// <summary>
/// Function linked to a callback function for the play button
/// </summary>
void MainMenu::playButtonSelected()
{
	playButtonPressed = true;
}

/// <summary>
/// Function linked to a callback function for the options button
/// </summary>
void MainMenu::optionsButtonSelected()
{
	optionsButtonPressed = true;
}

/// <summary>
/// Function linked to a callback function for the quit button
/// </summary>
void MainMenu::quitButtonSelected()
{
	exitButtonPressed = true;
}

/// <summary>
/// Function linked to a callback function for the credits button
/// </summary>
void MainMenu::creditsButtonSelected()
{
	creditsButtonsPressed = true;
}