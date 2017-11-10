#include "Screens\GameScreen.h"

GameScreen::GameScreen(XboxController &controller, sf::View &view)
	: Screen(GameState::GamePlay, view), isPaused(false)
{
	// @refactor(darren): Move this into scene manager and have all scens uses the same colors
	sf::Color focusIn(50, 200, 50);
	sf::Color focusOut(100, 20, 50);

	m_entityManager = EntityManager();
    m_player = new Player(controller);

	// Camera
	// @todo(refactor): make camera it's own class
	m_cameraPosition = *m_player->getPosition();

    m_entityManager.Add(m_player);
    m_entityManager.Add(new Enemy(m_player->getPosition()));

	if (!m_resumeTexture.loadFromFile("Assets/GUI/Resume.png"))
		std::cout << "Hey this resume texture didn't load, but that's just my opinion man...." << std::endl;

	if (!m_mainMenuTexture.loadFromFile("Assets/GUI/MainMenu.png"))
		std::cout << "Hey this main menu texture didn't load, but that's just my opinion man...." << std::endl;

	m_pauseLabel = new Label("PAUSED", 84);
	// @refactor(darren): Refactor the order of these parameters, don't need them.
	m_resume = new Button(m_resumeTexture, sf::Vector2f(1920.0f / 2.0f, (1080.0f / 2.0f) - 20.0f),
		focusIn, focusOut, 1.0f, 1.0f, sf::Vector2f((1920.0f / 2.0f) + 80.0f, (1080.0f / 2.0f) - 20.0f));
	m_mainMenu = new Button(m_mainMenuTexture, sf::Vector2f(1920.0f / 2.0f, (1080.0f / 2.0f) + 120.0f), 
		focusIn, focusOut, 1.0f, 1.0f, sf::Vector2f((1920.0f / 2.0f) + 80.0f, (1080.0f / 2.0f) + 120.0f));
	
	m_resume->select = std::bind(&GameScreen::resumeButtonSelected, this);
	m_mainMenu->select = std::bind(&GameScreen::mainMenuButtonSelected, this);

	m_resume->promoteFocus();

	m_resume->m_down = m_mainMenu;
	m_mainMenu->m_up = m_resume;

	m_gui.add(m_resume);
	m_gui.add(m_mainMenu);
	m_gui.add(m_pauseLabel);

	m_gui.setWidgetsAlpha(0.0f);
}

GameScreen::~GameScreen()
{
	
}

void GameScreen::reset()
{
	m_resume->promoteFocus();
	m_mainMenu->demoteFocus();
	interpolation = 0.0f;
}

void GameScreen::update(XboxController& controller, sf::Int32 dt)
{
	cameraFollow();
	m_cameraPosition += m_cameraVelocity * (float)dt;

	if (isPaused)
		m_gui.processInput(controller);
	else
	{
		m_entityManager.Update(dt);
		m_view.setCenter(m_cameraPosition);
	}

	if (controller.isButtonPressed(XBOX360_START) && !isPaused)
	{
		isPaused = true;
		transitionIn = true;
		setPauseGUIPos();
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

void GameScreen::render(sf::RenderTexture &renderTexture)
{
	renderTexture.setView(m_view);
    m_entityManager.Draw(renderTexture);
	if (isPaused)
	{
		renderTexture.setView(m_view);
		renderTexture.draw(m_gui);
	}
}

void GameScreen::cameraFollow()
{
	if (sf::distance(m_cameraPosition, *m_player->getPosition()) < 10.0f)
	{
		m_cameraVelocity = sf::Vector2f();
	}
	else
	{
		m_cameraVelocity = sf::normalize(*m_player->getPosition() - m_cameraPosition) * 0.25f;
	}
}

void GameScreen::setPauseGUIPos()
{
	sf::Vector2f guiCenter = m_cameraPosition;
	m_pauseLabel->setStartPos(sf::Vector2f(guiCenter.x, guiCenter.y - 300.0f));
	m_pauseLabel->setEndPos(sf::Vector2f(guiCenter.x - 80.0f, guiCenter.y - 300.0f));

	m_resume->setStartPos(sf::Vector2f(guiCenter.x, guiCenter.y - 80.0f));
	m_resume->setEndPos(sf::Vector2f(guiCenter.x + 80.0f, guiCenter.y - 80.0f));

	m_mainMenu->setStartPos(sf::Vector2f(guiCenter.x, guiCenter.y + 80.0f));
	m_mainMenu->setEndPos(sf::Vector2f(guiCenter.x + 80.0f, guiCenter.y + 80.0f));
}

void GameScreen::resumeButtonSelected()
{
	isPaused = false;
	reset();
}

void GameScreen::mainMenuButtonSelected()
{
	m_nextGameState = GameState::MainMenu;
	isPaused = false;
	reset();
}