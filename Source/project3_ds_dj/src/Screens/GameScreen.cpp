#include "Screens\GameScreen.h"
#include "Physics\ParticleManager.h"
#include <stdlib.h>

GameScreen::GameScreen(XboxController &controller, sf::View &view, 
	sf::Sound *confirmSound, sf::Sound *shotSound, sf::Sound *waveCompleteSound, 
	sf::Sound *shieldSound, sf::Sound *doubleBulletSound, sf::Sound *heartSound,
	sf::Sound *deathSound, sf::Sound *turretShotSound, sf::Sound *hitWallSound, sf::Sound *navigateSound) :
	Screen(GameState::GamePlay, view),
	m_isPaused(false),
	m_currentWave(1),
	m_entityManager(deathSound, shieldSound, doubleBulletSound, heartSound, hitWallSound, turretShotSound),
	m_confirmSound(confirmSound),
	m_shotSound(shotSound),
	m_turretShotSound(turretShotSound),
	m_waveCompleteSound(waveCompleteSound),
	m_navigateSound(navigateSound)
{
	// @refactor(darren): Move this into scene manager and have all scens uses the same colors
	sf::Color focusIn(50, 200, 50);
	sf::Color focusOut(100, 20, 50);

    m_player = new Player(controller, m_shotSound);
	m_entityManager.SetPlayer(m_player);
	
	m_maxEnemies = 5;	// The number of enemies.
    m_entityManager.CreateEnemies(m_maxEnemies);

	// Set the wave for the game and display on the hud
	m_hud.setWave(m_currentWave);

	// Camera
	m_cameraPosition = *m_player->getPosition();

	m_resumeTexture.loadFromFile("Assets/GUI/Resume.png");
	m_retryTexture.loadFromFile("Assets/GUI/Retry.png");
	m_mainMenuTexture.loadFromFile("Assets/GUI/MainMenu.png");
	m_arrowTextureUp.loadFromFile("Assets/GUI/arrowUp.png");
	m_arrowTextureDown.loadFromFile("Assets/GUI/arrowDown.png");

	m_pauseLabel = new Label("PAUSED", 84);
	m_gameOverLabel = new Label("GAME OVER", 84);
	m_gameOverLabel->setTextColor(sf::Color(255, 0, 0));
	m_enterNameMessageLabel = new Label("High score achieved, please enter your name", 30);
	m_enterNameMessageLabel->setTextColor(sf::Color(255, 0, 0));
	// @refactor(darren): Refactor the order of these parameters, don't need them.
	m_resume = new Button(m_confirmSound, m_navigateSound, m_resumeTexture, sf::Vector2f(),
		focusIn, focusOut, 1.0f, 1.0f, sf::Vector2f());
	m_mainMenu = new Button(m_confirmSound, m_navigateSound, m_mainMenuTexture, sf::Vector2f(1920.0f / 2.0f, (1080.0f / 2.0f) + 120.0f),
		focusIn, focusOut, 1.0f, 1.0f, sf::Vector2f((1920.0f / 2.0f) + 80.0f, (1080.0f / 2.0f) + 120.0f));
	m_mainMenuGameOver = new Button(m_confirmSound, m_navigateSound, m_mainMenuTexture, sf::Vector2f(1920.0f / 2.0f, (1080.0f / 2.0f) + 120.0f),
		focusIn, focusOut, 1.0f, 1.0f, sf::Vector2f((1920.0f / 2.0f) + 80.0f, (1080.0f / 2.0f) + 120.0f));
	m_retry = new Button(m_confirmSound, m_navigateSound, m_retryTexture, sf::Vector2f(1920.0f / 2.0f, (1080.0f / 2.0f) - 20.0f),
		focusIn, focusOut, 1.0f, 1.0f, sf::Vector2f((1920.0f / 2.0f) + 80.0f, (1080.0f / 2.0f) - 20.0f));

	for (int i = 0; i < 6; i++)
	{
		if (i > 2)
			m_arrowButtons[i] = new Button(m_confirmSound, m_navigateSound, m_arrowTextureUp, sf::Vector2f(), focusIn, focusOut, 0.75f, 0.75f, sf::Vector2f());
		else
			m_arrowButtons[i] = new Button(m_confirmSound, m_navigateSound, m_arrowTextureDown, sf::Vector2f(), focusIn, focusOut, 0.75f, 0.75f, sf::Vector2f());
	}

	m_charNameLabels[0] = new Label("A", 60);
	m_charNameLabels[1] = new Label("A", 60);
	m_charNameLabels[2] = new Label("A", 60);
	
	m_resume->select = std::bind(&GameScreen::resumeButtonSelected, this);
	m_mainMenu->select = std::bind(&GameScreen::mainMenuButtonResumeSelected, this);
	m_retry->select = std::bind(&GameScreen::retryButtonSelected, this);
	m_mainMenuGameOver->select = std::bind(&GameScreen::mainMenuButtonGameOverSelected, this);

	m_resume->promoteFocus();

	m_resume->m_down = m_mainMenu;
	m_mainMenu->m_up = m_resume;

	m_gui.add(m_resume);
	m_gui.add(m_mainMenu);
	m_gui.add(m_pauseLabel);

	m_retry->m_up = m_arrowButtons[3];
	m_retry->m_down = m_mainMenuGameOver;
	m_mainMenuGameOver->m_up = m_retry;

	m_arrowButtons[0]->promoteFocus();
	m_arrowButtons[0]->m_right = m_arrowButtons[1];
	m_arrowButtons[0]->m_down = m_arrowButtons[3];

	auto arrowFunc0 = [&]() { m_charNameIndex[0] = (m_charNameIndex[0] + 1) % MAX_USER_NAME_CHARS; };
	m_arrowButtons[0]->select = std::bind(arrowFunc0);
	auto arrowFunc1 = [&]() { m_charNameIndex[1] = (m_charNameIndex[1] + 1) % MAX_USER_NAME_CHARS; };
	m_arrowButtons[1]->select = std::bind(arrowFunc1);
	auto arrowFunc2 = [&]() { m_charNameIndex[2] = (m_charNameIndex[2] + 1) % MAX_USER_NAME_CHARS; };
	m_arrowButtons[2]->select = std::bind(arrowFunc2);
	auto arrowFunc3 = [&]() { m_charNameIndex[0] = (m_charNameIndex[0] + MAX_USER_NAME_CHARS - 1) % MAX_USER_NAME_CHARS;};
	m_arrowButtons[3]->select = std::bind(arrowFunc3);
	auto arrowFunc4 = [&]() { m_charNameIndex[1] = (m_charNameIndex[1] + MAX_USER_NAME_CHARS - 1) % MAX_USER_NAME_CHARS; };
	m_arrowButtons[4]->select = std::bind(arrowFunc4);
	auto arrowFunc5 = [&]() { m_charNameIndex[2] = (m_charNameIndex[2] + MAX_USER_NAME_CHARS - 1) % MAX_USER_NAME_CHARS; };
	m_arrowButtons[5]->select = std::bind(arrowFunc5);

	m_arrowButtons[1]->m_left = m_arrowButtons[0];
	m_arrowButtons[1]->m_right = m_arrowButtons[2];
	m_arrowButtons[1]->m_down = m_arrowButtons[4];
	m_arrowButtons[2]->m_left = m_arrowButtons[1];
	m_arrowButtons[2]->m_down = m_arrowButtons[5];
	m_arrowButtons[3]->m_up = m_arrowButtons[0];
	m_arrowButtons[3]->m_right = m_arrowButtons[4];
	m_arrowButtons[3]->m_down = m_retry;
	m_arrowButtons[4]->m_up = m_arrowButtons[1];
	m_arrowButtons[4]->m_left = m_arrowButtons[3];
	m_arrowButtons[4]->m_right = m_arrowButtons[5];
	m_arrowButtons[4]->m_down = m_retry;
	m_arrowButtons[5]->m_up = m_arrowButtons[2];
	m_arrowButtons[5]->m_left = m_arrowButtons[4];
	m_arrowButtons[5]->m_down = m_retry;

	for (int i = 0; i < 6; i++)
		m_gameOverGui.add(m_arrowButtons[i]);

	for (int i = 0; i < 3; i++)
		m_gameOverGui.add(m_charNameLabels[i]);

	m_gameOverGui.add(m_retry);
	m_gameOverGui.add(m_mainMenuGameOver);
	m_gameOverGui.add(m_gameOverLabel);
	m_gameOverGui.add(m_enterNameMessageLabel);

	m_gui.setWidgetsAlpha(0.0f);
	m_gameOverGui.setWidgetsAlpha(0.0f);

	m_hud.setScore(100);
}

void GameScreen::reset()
{
	m_arrowButtons[0]->promoteFocus();
	m_resume->promoteFocus();
	m_retry->demoteFocus();
	m_mainMenuGameOver->demoteFocus();
	m_mainMenu->demoteFocus();
	interpolation = 0.0f;
}

void GameScreen::update(XboxController& controller, sf::Int32 dt)
{
	m_hud.setMultiplier(m_entityManager.GetMultiplier());

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
		cameraFollow();

		if (m_isGameOver)
		{
			m_gameOverGui.processInput(controller);

			for (int i = 0; i < 3; i++)
			{
				m_charNameLabels[i]->setText(m_userNameChars[m_charNameIndex[i]]);
			}
		}

		if (!m_player->getAlive() && !m_isGameOver)
		{
			m_player->SpawnPlayer(false);
		}

		if (m_player->getAlive() && !m_playerWasAlive)
		{
			m_entityManager.reset();
			m_currentWave--;
		}

		m_hud.setLives(m_player->m_lives);
		m_hud.update(dt, m_cameraPosition);
		
		if (m_player->FireBullet())
		{
			if (m_player->getBulletType() == BulletType::SINGLE_BULLET)
			{
				//m_entityManager.AddBullet(new Bullet(*m_player->getPosition(), sf::normalize(controller.getLeftStick()), true));	//	This exists so the game can be tested with a ps4 controller.
				m_entityManager.AddBullet(new Bullet(*m_player->getPosition(), 
					sf::normalize(controller.getRightStick()), sf::Color(255, 255, 255), true));
			}
			else if (m_player->getBulletType() == BulletType::DOUBLE_BULLET)
			{
				sf::Vector2f offset = sf::Vector2f(sf::randF(-20, 20), sf::randF(-20, 20));
				m_entityManager.AddBullet(new Bullet(*m_player->getPosition() + offset,
					sf::normalize(controller.getRightStick()), sf::Color(226, 219, 9), true));
				m_entityManager.AddBullet(new Bullet(*m_player->getPosition() - offset,
					sf::normalize(controller.getRightStick()), sf::Color(226, 219, 9), true));
			}
		}

		m_entityManager.Update(dt, *m_hud.getScore());

		for (auto iter = m_entityManager.GetEnemies().begin(); iter != m_entityManager.GetEnemies().end(); iter++)
		{
			if ((*iter)->getFireBullet())
			{
				m_entityManager.AddBullet(new Bullet((*iter)->getPos(), sf::normalize(sf::Vector2f(m_player->getPos().x - (*iter)->getPos().x, 
					m_player->getPos().y - (*iter)->getPos().y)), sf::Color(214, 105, 17), false));
			}
		}

		m_view.setCenter(m_cameraPosition);

		if (m_player->m_lives <= 0)
		{
			m_player->StopVibration();

			if (!m_isGameOver)
			{
				transitionIn = true;
				m_isGameOver = true;
				m_minimumLeaderboardScore = findMinimumLeaderboardScore();
				setGameOverGUIPos();
			}
		}
	}

	if (controller.isButtonPressed(XBOX360_START) && !m_isPaused && !m_isGameOver)
	{
		m_isPaused = true;
		transitionIn = true;
		setPauseGUIPos();
		Grid::instance()->setPause(true);
		ParticleManager::instance()->setPause(true);
		m_player->StopVibration();
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

	m_playerWasAlive = m_player->getAlive();
}

void GameScreen::spawnPowerUp()
{
	if (m_entityManager.GetPowerUp() == nullptr)
	{
		sf::Vector2f randomPos = sf::Vector2f(sf::randF(150.0f, 1500.0f), sf::randF(150.0f, 1000.0f));
		int randomPowerUp = sf::randF(0, 3);
		if (randomPowerUp == 0)
			m_entityManager.AddPowerUp(new ShieldPower(randomPos));
		else if (randomPowerUp == 1)
			m_entityManager.AddPowerUp(new HeartPower(randomPos));
		else if (randomPowerUp == 2)
			m_entityManager.AddPowerUp(new DoubleBulletPowerUp(randomPos));
	}
}

void GameScreen::setWave(uint8_t waveNum)
{
	// @note(darren)	:(
	if (!m_leftViaPause)
	{
		m_hud.setWave(waveNum);
		m_waveCompleteSound->play();
		spawnPowerUp();

        m_entityManager.CreateEnemies(m_maxEnemies * waveNum);
	}
	else
	{
		m_hud.setWave(waveNum);
		spawnPowerUp();

        m_entityManager.CreateEnemies(m_maxEnemies * waveNum);

		m_leftViaPause = false;
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
	m_pauseLabel->setStartPos(sf::Vector2f(guiCenter.x, guiCenter.y - 250.0f));
	m_pauseLabel->setEndPos(sf::Vector2f(guiCenter.x - 80.0f, guiCenter.y - 250.0f));

	m_resume->setStartPos(sf::Vector2f(guiCenter.x, guiCenter.y - 10.0f));
	m_resume->setEndPos(sf::Vector2f(guiCenter.x + 80.0f, guiCenter.y - 10.0f));

	m_mainMenu->setStartPos(sf::Vector2f(guiCenter.x, guiCenter.y + 150.0f));
	m_mainMenu->setEndPos(sf::Vector2f(guiCenter.x + 80.0f, guiCenter.y + 150.0f));
}

void GameScreen::setGameOverGUIPos()
{
	uint32_t currentScore = *m_hud.getScore();
	sf::Vector2f guiCenter = m_cameraPosition;

	if (currentScore > m_minimumLeaderboardScore)
	{

		m_retry->demoteFocus();
		m_arrowButtons[0]->promoteFocus();
		m_enterNameMessageLabel->m_isActive = true;
		for (int i = 0; i < 6; i++)
		{
			float gap = 120.0f;

			if (i <= 2)
			{
				m_charNameLabels[i]->m_isActive = true;
				m_charNameLabels[i]->setStartPos(sf::Vector2f(guiCenter.x + (gap * i) - gap, guiCenter.y - 170.0f));
				m_charNameLabels[i]->setEndPos(sf::Vector2f(guiCenter.x + (gap * i) - gap, guiCenter.y - 170.0f));
			}

			m_arrowButtons[i]->m_isActive = true;
			if (i <= 2)
			{
				m_arrowButtons[i]->setStartPos(sf::Vector2f(guiCenter.x + (gap * i) - gap, guiCenter.y - 220.0f));
				m_arrowButtons[i]->setEndPos(sf::Vector2f(guiCenter.x + (gap * i) - gap, guiCenter.y - 220.0f));
			}
			else
			{
				m_arrowButtons[i]->setStartPos(sf::Vector2f(guiCenter.x + (gap * (i - 3) - gap), guiCenter.y - 100.0f));
				m_arrowButtons[i]->setEndPos(sf::Vector2f(guiCenter.x + (gap * (i - 3) - gap), guiCenter.y - 100.0f));
			}
		}

		m_gameOverLabel->setStartPos(sf::Vector2f(guiCenter.x, guiCenter.y - 400.0f));
		m_gameOverLabel->setEndPos(sf::Vector2f(guiCenter.x - 80.0f, guiCenter.y - 400.0f));

		m_enterNameMessageLabel->setStartPos(sf::Vector2f(guiCenter.x, guiCenter.y - 300.0f));
		m_enterNameMessageLabel->setEndPos(sf::Vector2f(guiCenter.x - 80.0f, guiCenter.y - 300.0f));

		m_retry->m_up = m_arrowButtons[3];
		m_retry->setStartPos(sf::Vector2f(guiCenter.x, guiCenter.y + 20.0f));
		m_retry->setEndPos(sf::Vector2f(guiCenter.x + 80.0f, guiCenter.y + 20.0f));

		m_mainMenuGameOver->setStartPos(sf::Vector2f(guiCenter.x, guiCenter.y + 180.0f));
		m_mainMenuGameOver->setEndPos(sf::Vector2f(guiCenter.x + 80.0f, guiCenter.y + 180.0f));
	}
	else
	{
		m_enterNameMessageLabel->m_isActive = false;
		for (int i = 0; i < 6; i++)
		{
			if (i <= 2)
				m_charNameLabels[i]->m_isActive = false;

			m_arrowButtons[i]->m_isActive = false;
		}

		m_gameOverLabel->setStartPos(sf::Vector2f(guiCenter.x, guiCenter.y - 250.0f));
		m_gameOverLabel->setEndPos(sf::Vector2f(guiCenter.x - 80.0f, guiCenter.y - 250.0f));

		m_retry->m_up = nullptr;
		m_arrowButtons[0]->demoteFocus();
		m_retry->promoteFocus();
		m_retry->setStartPos(sf::Vector2f(guiCenter.x, guiCenter.y - 10.0f));
		m_retry->setEndPos(sf::Vector2f(guiCenter.x + 80.0f, guiCenter.y - 10.0f));

		m_mainMenuGameOver->setStartPos(sf::Vector2f(guiCenter.x, guiCenter.y + 150.0f));
		m_mainMenuGameOver->setEndPos(sf::Vector2f(guiCenter.x + 80.0f, guiCenter.y + 150.0f));
	}
}

void GameScreen::resumeButtonSelected()
{
	m_isPaused = false;
	Grid::instance()->setPause(false);
	ParticleManager::instance()->setPause(false);
	m_confirmSound->play();
	reset();
}

void GameScreen::mainMenuButtonGameOverSelected()
{
	m_nextGameState = GameState::MainMenu;
	m_isPaused = false;
	Grid::instance()->setPause(false);
	ParticleManager::instance()->setPause(false);
	m_leftViaPause = true;
	m_isGameOver = false;

	updateLeaderboard();

	//	Reset the player.
	m_player->m_lives = 3;
	m_player->setAlive(true);
	m_player->SpawnPlayer(true);
	m_player->StopVibration();
	//	Reset the hud
	m_currentWave = 0;
	m_hud.setScore(0);
	m_hud.setWave(m_currentWave);
	//	Reset all other entitys
	m_entityManager.reset();

	reset();
}

void GameScreen::mainMenuButtonResumeSelected()
{
	m_nextGameState = GameState::MainMenu;
	m_isPaused = false;
	Grid::instance()->setPause(false);
	ParticleManager::instance()->setPause(false);
	m_leftViaPause = true;
	m_isGameOver = false;
	m_player->m_lives = 3;
	m_player->setAlive(true);
	m_player->SpawnPlayer(true);
	m_player->StopVibration();
	m_currentWave = 0;
	m_hud.setScore(0);
	m_hud.setWave(m_currentWave);
	m_entityManager.reset();
	reset();
}

void GameScreen::retryButtonSelected()
{
	updateLeaderboard();
	m_isGameOver = false;
	m_currentWave = 0;
	m_hud.setScore(0);
	m_hud.setWave(m_currentWave);
	m_entityManager.reset();
	m_player->SpawnPlayer(true);
	m_player->setAlive(true);
	m_player->m_lives = 3;
}

uint32_t GameScreen::findMinimumLeaderboardScore()
{
	std::ifstream inputLeaderboardFile;
	inputLeaderboardFile.open("leaderboard.txt");
	uint32_t lowestScore = 0;

	if (inputLeaderboardFile.is_open())
	{
		for (int i = 0; i < 10; i++)
		{
			std::string name = "";
			uint32_t score = 0;
			inputLeaderboardFile >> name >> score;

			if (i == 9)
				lowestScore = score;
		}
	}

	inputLeaderboardFile.close();

	return lowestScore;
}

void GameScreen::updateLeaderboard()
{
	//	Read all the scores from the leaderboard text file.
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

	//	Get the current score.
	auto currentScore = m_hud.getScore();

	for (int i = 0; i < 10; i++)
	{
		//	Check if the current score is better then any score.
		if (*currentScore > m_readInScores[i])
		{
			std::ofstream outputLeaderboardFile;
			outputLeaderboardFile.open("leaderboard.txt");
			if (outputLeaderboardFile.is_open())
			{
				//	Rewrite the scores better then the current score.
				for (int j = 0; j < i; j++)
				{
					outputLeaderboardFile << m_readInNames[j] << " " << m_readInScores[j] << "\n";
				}

				//	Write the current score.
				outputLeaderboardFile << m_userNameChars[m_charNameIndex[0]] << m_userNameChars[m_charNameIndex[1]] << m_userNameChars[m_charNameIndex[2]] << " " << *currentScore << "\n";

				//	Rewrite the scores worse then the current score.
				for (int k = i; k < 10; k++)
				{
					outputLeaderboardFile << m_readInNames[k] << " " << m_readInScores[k] << "\n";
				}

			}

			outputLeaderboardFile.close();
			break;
		}
	}
}
