#include "Screens\GameScreen.h"
#include "Physics\ParticleManager.h"

GameScreen::GameScreen(XboxController &controller, sf::View &view, sf::Sound *confirmSound, 
	sf::Sound *shotSound, sf::Sound *waveCompleteSound, 
	sf::Sound *pickUpSound, sf::Sound *deathSound, sf::Sound *hitWallSound) :
	Screen(GameState::GamePlay, view),
	m_isPaused(false),
	m_currentWave(1),
	m_entityManager(deathSound, pickUpSound, hitWallSound),
	m_confirmSound(confirmSound),
	m_shotSound(shotSound),
	m_waveCompleteSound(waveCompleteSound)
{
	// @refactor(darren): Move this into scene manager and have all scens uses the same colors
	sf::Color focusIn(50, 200, 50);
	sf::Color focusOut(100, 20, 50);

    m_player = new Player(controller, m_shotSound);

	m_entityManager.SetPlayer(m_player);
	m_entityManager.AddPowerUp(new ShieldPower(sf::Vector2f(400.0f, 500.0f)));

	m_maxEnemies = 5;	// The number of enemies.
	for (int i = 0; i < m_maxEnemies; i++)
	{
		m_entityManager.AddEnemy(new Enemy(m_player->getPosition()));
	}

	// Set the wave for the game and display on the hud
	m_hud.setWave(m_currentWave);

	// Camera
	m_cameraPosition = *m_player->getPosition();

	if (!m_resumeTexture.loadFromFile("Assets/GUI/Resume.png"))
		std::cout << "Hey this resume texture didn't load, but that's just my opinion man...." << std::endl;

	if (!m_mainMenuTexture.loadFromFile("Assets/GUI/MainMenu.png"))
		std::cout << "Hey this main menu texture didn't load, but that's just my opinion man...." << std::endl;

	m_pauseLabel = new Label("PAUSED", 84);
	m_gameOverLabel = new Label("GAME OVER", 84);
	m_gameOverLabel->setTextColor(sf::Color(255, 0, 0));
	// @refactor(darren): Refactor the order of these parameters, don't need them.
	m_resume = new Button(m_resumeTexture, sf::Vector2f(1920.0f / 2.0f, (1080.0f / 2.0f) - 20.0f),
		focusIn, focusOut, 1.0f, 1.0f, sf::Vector2f((1920.0f / 2.0f) + 80.0f, (1080.0f / 2.0f) - 20.0f));
	m_mainMenu = new Button(m_mainMenuTexture, sf::Vector2f(1920.0f / 2.0f, (1080.0f / 2.0f) + 120.0f), 
		focusIn, focusOut, 1.0f, 1.0f, sf::Vector2f((1920.0f / 2.0f) + 80.0f, (1080.0f / 2.0f) + 120.0f));
	m_mainMenuGameOver = new Button(m_mainMenuTexture, sf::Vector2f(1920.0f / 2.0f, (1080.0f / 2.0f) + 120.0f),
		focusIn, focusOut, 1.0f, 1.0f, sf::Vector2f((1920.0f / 2.0f) + 80.0f, (1080.0f / 2.0f) + 120.0f));
	m_retry = new Button(m_resumeTexture, sf::Vector2f(1920.0f / 2.0f, (1080.0f / 2.0f) - 20.0f),
		focusIn, focusOut, 1.0f, 1.0f, sf::Vector2f((1920.0f / 2.0f) + 80.0f, (1080.0f / 2.0f) - 20.0f));
	
	m_resume->select = std::bind(&GameScreen::resumeButtonSelected, this);
	m_mainMenu->select = std::bind(&GameScreen::mainMenuButtonSelected, this);
	m_retry->select = std::bind(&GameScreen::retryButtonSelected, this);
	m_mainMenuGameOver->select = std::bind(&GameScreen::mainMenuButtonSelected, this);

	m_resume->promoteFocus();
	m_retry->promoteFocus();

	m_resume->m_down = m_mainMenu;
	m_mainMenu->m_up = m_resume;

	m_gui.add(m_resume);
	m_gui.add(m_mainMenu);
	m_gui.add(m_pauseLabel);

	m_retry->m_down = m_mainMenuGameOver;
	m_mainMenuGameOver->m_up = m_retry;

	m_gameOverGui.add(m_retry);
	m_gameOverGui.add(m_mainMenuGameOver);
	m_gameOverGui.add(m_gameOverLabel);

	m_gui.setWidgetsAlpha(0.0f);
	m_gameOverGui.setWidgetsAlpha(0.0f);

	m_hud.setScore(100);
}

void GameScreen::reset()
{
	m_resume->promoteFocus();
	m_mainMenu->demoteFocus();
	m_retry->promoteFocus();
	interpolation = 0.0f;
}

void GameScreen::update(XboxController& controller, sf::Int32 dt)
{
	// Increase wave when all enemies are dead.
	if (m_entityManager.GetEnemiesSize() == 0)
	{
		m_currentWave++;
		setWave(m_currentWave);
	}

	if (m_isPaused)
		m_gui.processInput(controller);
	else
	{
		if(m_isGameOver)
			m_gameOverGui.processInput(controller);

		if (m_player->m_lives <= 0)
		{
			if (!m_isGameOver)
			{
				setGameOverGUIPos();
				transitionIn = true;
				m_isGameOver = true;
			}
		}

		cameraFollow();
		m_hud.setLives(m_player->m_lives);
		m_hud.update(dt, m_cameraPosition);
		if (m_player->FireBullet())
		{
			if(m_player->getBulletType() == BulletType::SINGLE_BULLET)
				m_entityManager.AddBullet(new Bullet(*m_player->getPosition(), sf::normalize(controller.getLeftStick())));
			// @todo(darren): Fix an issue with double bullets
			else if (m_player->getBulletType() == BulletType::DOUBLE_BULLET)
			{
				sf::Vector2f offset = sf::Vector2f(sf::randF(0, 10), sf::randF(-20, 20));
				m_entityManager.AddBullet(new Bullet(*m_player->getPosition() + offset,
					sf::normalize(controller.getRightStick())));
				m_entityManager.AddBullet(new Bullet(*m_player->getPosition() - offset,
					sf::normalize(controller.getRightStick())));
			}
			else if (m_player->getBulletType() == BulletType::MISSILE_HOMING)
			{
				// Find an enemey position to track
				// @todo(darren): This does not work, get basic bullets working first and gameplay loop
				std::vector<Entity*> enemies = m_entityManager.GetEnemies();
				int randIndex = static_cast<int>(sf::randF(0, enemies.size()));
				sf::Vector2f *enemyPos = &enemies[randIndex]->getPos();
				m_entityManager.AddBullet(new HomingMissile(*m_player->getPosition(), sf::normalize(controller.getLeftStick()), enemyPos));
			}
		}

		m_entityManager.Update(dt, *m_hud.getScore());
		m_view.setCenter(m_cameraPosition);
	}

	if (controller.isButtonPressed(XBOX360_START) && !m_isPaused && !m_isGameOver)
	{
		m_isPaused = true;
		transitionIn = true;
		setPauseGUIPos();
		Grid::instance()->setPause(true);
		ParticleManager::instance()->setPause(true);
	}

	if (transitionIn)
	{
		m_gui.transitionIn(0.05f, interpolation);
		m_gameOverGui.transitionIn(0.05f, interpolation);

		if (interpolation >= 1.0f)
		{
			interpolation = 0.0f;
			transitionIn = false;
		}
	}
}

void GameScreen::setWave(uint8_t waveNum)
{
	if (m_leftViaPause)
	{
		m_hud.setWave(waveNum);

		for (int i = 0; i < m_maxEnemies * waveNum; i++)
		{
			m_entityManager.AddEnemy(new Enemy(m_player->getPosition()));
		}
	}
	else
	{
		m_hud.setWave(waveNum);
		m_waveCompleteSound->play();

		for (int i = 0; i < m_maxEnemies * waveNum; i++)
		{
			m_entityManager.AddEnemy(new Enemy(m_player->getPosition()));
		}
	}
}

void GameScreen::render(sf::RenderTexture &renderTexture)
{
	renderTexture.setView(m_view);
	m_hud.render(renderTexture);
    m_entityManager.Draw(renderTexture);

	if (m_isGameOver)
	{
		renderTexture.draw(m_gameOverGui);
	}
	else if (m_isPaused)
	{
		renderTexture.setView(m_view);
		renderTexture.draw(m_gui);
	}
}

void GameScreen::cameraFollow()
{
	m_cameraPosition += (*m_player->getPosition() - m_cameraPosition) * 0.1f;
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

void GameScreen::setGameOverGUIPos()
{
	sf::Vector2f guiCenter = m_cameraPosition;
	m_gameOverLabel->setStartPos(sf::Vector2f(guiCenter.x, guiCenter.y - 300.0f));
	m_gameOverLabel->setEndPos(sf::Vector2f(guiCenter.x - 80.0f, guiCenter.y - 300.0f));

	m_retry->setStartPos(sf::Vector2f(guiCenter.x, guiCenter.y - 80.0f));
	m_retry->setEndPos(sf::Vector2f(guiCenter.x + 80.0f, guiCenter.y - 80.0f));

	m_mainMenuGameOver->setStartPos(sf::Vector2f(guiCenter.x, guiCenter.y + 80.0f));
	m_mainMenuGameOver->setEndPos(sf::Vector2f(guiCenter.x + 80.0f, guiCenter.y + 80.0f));
}

void GameScreen::resumeButtonSelected()
{
	m_isPaused = false;
	Grid::instance()->setPause(false);
	ParticleManager::instance()->setPause(false);
	m_confirmSound->play();
	reset();
}

void GameScreen::mainMenuButtonSelected()
{
	m_nextGameState = GameState::MainMenu;
	m_isPaused = false;
	Grid::instance()->setPause(false);
	ParticleManager::instance()->setPause(false);
	m_currentWave = 0;
	m_hud.setWave(m_currentWave);
	m_leftViaPause = true;
	for (Entity* enemy : m_entityManager.GetEnemies())
		enemy->setAlive(false);
	m_entityManager.GetEnemyScores().clear();
	m_player->m_lives = 1;
	m_confirmSound->play();
	reset();
}


void GameScreen::retryButtonSelected()
{
	m_isGameOver = false;
	m_player->m_lives = 1;
	m_player->setAlive(true);
	m_player->SpawnPlayer(true);
	m_currentWave = 0;
	m_hud.setWave(m_currentWave);
	for (Entity* enemy : m_entityManager.GetEnemies())
		enemy->setAlive(false);
	m_entityManager.GetEnemyScores().clear();
}