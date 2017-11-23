#include "Screens\MainMenu.h"

MainMenu::MainMenu(sf::View &view)
	: Screen(GameState::MainMenu, view), m_alphaFadeValue(255)
{
	sf::Color focusIn(50, 200, 50);
	sf::Color focusOut(100, 20, 50);

	m_fadeRectangle.setSize(sf::Vector2f(1920.0f, 1080.0f));
	m_fadeRectangle.setFillColor(sf::Color(0.0f, 0.0f, 0.0f, m_alphaFadeValue));

	if (!m_playTexture.loadFromFile("Assets/GUI/PlayButton.png"))
		std::cout << "ERROR::Player::Image not loaded";

	if (!m_optionsTexture.loadFromFile("Assets/GUI/OptionsButton.png"))
		std::cout << "ERROR::Player::Image not loaded";

	if (!m_creditsTexture.loadFromFile("Assets/GUI/CreditsButton.png"))
		std::cout << "ERROR::Player::Image not loaded";

	if (!m_exitTexture.loadFromFile("Assets/GUI/ExitButton.png"))
		std::cout << "ERROR::Player::Image not loaded";

	m_playButton = new Button(m_playTexture, sf::Vector2f(1920 / 2, 400.0f),
		focusIn, focusOut, 1.0f, 1.0f, sf::Vector2f(1920.0f / 2 + 400.0f, 400.0f));
	m_optionsButton = new Button(m_optionsTexture, sf::Vector2f(1920 / 2, 500.0f),
		focusIn, focusOut, 1.0f, 1.0f, sf::Vector2f(1920.0f / 2 + 400.0f, 500.0f));
	m_creditsButton = new Button(m_creditsTexture, sf::Vector2f(1920 / 2, 600.0f),
		focusIn, focusOut, 1.0f, 1.0f, sf::Vector2f(1920.0f / 2 + 400.0f, 600.0f));
	m_exitButton = new Button(m_exitTexture, sf::Vector2f(1920 / 2, 700.0f),
		focusIn, focusOut, 1.0f, 1.0f, sf::Vector2f(1920.0f / 2 + 400.0f, 700.0f));

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

	m_gui.add(m_playButton);
	m_gui.add(m_optionsButton);
	m_gui.add(m_creditsButton);
	m_gui.add(m_exitButton);

	if (!m_gameLogoTexture.loadFromFile("Assets/game_logo.png"))
		std::cout << "ERROR::Player::Image not loaded";

	m_gameLogoSprite.setTexture(m_gameLogoTexture);
	m_gameLogoSprite.setPosition(sf::Vector2f(1920.0f / 2, 150.0f));
	m_gameLogoSprite.setScale(sf::Vector2f(0.40f, 0.40f));
	m_gameLogoSprite.setOrigin(m_gameLogoSprite.getLocalBounds().width / 2.0f, m_gameLogoSprite.getLocalBounds().height / 2.0f);
}

/// <summary>
/// Reset function used to reset the main menu after the game state has been changed
/// </summary>
void MainMenu::reset()
{
	optionsButtonPressed = false;
	exitButtonPressed = false;
	playButtonPressed = false;
	creditsButtonsPressed = false;
	transitionIn = true;
	interpolation = 0.0f;
}

/// <summary>
/// update function updates the main menu and its GUI
/// </summary>
/// <param name="controller">Controller used for processing input</param>
void MainMenu::update(XboxController &controller, sf::Int32 dt)
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
			m_nextGameState = GameState::PlayMenu; 
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
/// <param name="window">render texture usd to render the GUI and fade rectangle</param>
void MainMenu::render(sf::RenderTexture & renderTexture)
{
	renderTexture.setView(m_view);
	renderTexture.draw(m_gui);
	renderTexture.draw(m_gameLogoSprite);
	renderTexture.draw(m_fadeRectangle);
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