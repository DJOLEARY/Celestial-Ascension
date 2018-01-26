#include "Game.h"

Game::Game()
	:
	m_windowSettings(),
	m_window(sf::VideoMode::getDesktopMode(), "Project 3 - Darren & D.J", sf::Style::Default, m_windowSettings),
	m_xboxController(CONTROLLER_ONE),
	m_view(sf::FloatRect(0, 0, 1920, 1080)),
	m_bloom(m_window.getSize(), 0.0f, 1.0f)
{
	std::cout << "openGL version:" << m_window.getSettings().majorVersion 
		<< "." << m_window.getSettings().minorVersion << std::endl << std::endl;

	m_view.zoom(1.0f);
	m_window.setMouseCursorVisible(false);

	if (!m_music.openFromFile("Assets/Sounds/GameMusic.wav"))
	{
		std::cout << "ERROR::Game::music not loaded";
	}
	m_musicPlaying = true;
	m_music.setVolume(100);
	m_music.setLoop(true);
	m_music.play();

	if (!m_confirmBuffer.loadFromFile("Assets/Sounds/MenuSelect.wav"))
	{
		std::cout << "ERROR::Game:confirmBuffer not loaded";
	}
	m_confirmSound.setBuffer(m_confirmBuffer);

	m_screenManager.add(new SplashScreen(m_view));
	m_screenManager.add(new MainMenu(m_view, &m_confirmSound));
	m_options = new Options(m_view, &m_confirmSound);
	m_screenManager.add(m_options);
	exitMenu = new ExitMenu(m_view, &m_confirmSound);
	m_screenManager.add(exitMenu);
	m_screenManager.add(new Credits(m_view));
	m_screenManager.add(new PlayMenu(m_view, &m_confirmSound));

	// I HATE SOUND 
	m_options->m_muted = true;

    m_screenManager.add(new GameScreen(m_xboxController, m_view, &m_options->m_muted, &m_options->m_effectsVolumeValue, &m_options->m_effectsVolumeChanged));

	std::cout << m_window.getSize().x << " " << m_window.getSize().y << std::endl;

	if (!m_renderTexture.create(m_view.getSize().x, m_view.getSize().y))
		std::cout << "Render texture not created" << std::endl;
}

void Game::run()
{
    sf::Clock clock;
    sf::Int32 lag = 0;

	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const sf::Time timePerFrame = sf::seconds(1.0f / 60.0f);
	timeSinceLastUpdate = clock.restart();

    // Start the game loop
    while (!exitMenu->getExitState())
    {
        // Process events
        sf::Event event;
        while (m_window.pollEvent(event))
        {
            // Close window : exit
            if (event.type == sf::Event::Closed)
                m_window.close();
        }

		if (m_options->m_goToFullscreenMode && !m_inFullscreenMode)
		{
			m_window.create(sf::VideoMode::getDesktopMode(), "Project 3 - Darren & D.J", sf::Style::Fullscreen, m_windowSettings);
			m_window.setMouseCursorVisible(false);
			m_options->m_goToFullscreenMode = false;
			m_inFullscreenMode = true;
			m_inWindowedMode = false;
		}
		else if(m_options->m_goToWindowedMode && !m_inWindowedMode)
		{
			m_window.create(sf::VideoMode::getDesktopMode(), "Project 3 - Darren & D.J", sf::Style::Default, m_windowSettings);
			m_window.setMouseCursorVisible(false);
			m_options->m_goToWindowedMode = false;
			m_inWindowedMode = true;
			m_inFullscreenMode = false;
		}
		
		if (m_options->m_muted)
		{
			m_confirmSound.setVolume(0);
			m_music.pause();
			m_musicPlaying = false;
		}
		else if (!m_options->m_muted && m_musicPlaying == false)
		{
			m_confirmSound.setVolume(m_options->m_effectsVolumeValue);
			m_music.play();
			m_musicPlaying = true;
		}

		if (m_options->m_musicVolumeChanged && !m_options->m_muted)
		{
			m_music.setVolume(m_options->m_musicVolumeValue);
			m_options->m_musicVolumeChanged = false;
		}

		if (m_options->m_effectsVolumeChanged && !m_options->m_muted)
		{
			m_confirmSound.setVolume(m_options->m_effectsVolumeValue);
		}

		timeSinceLastUpdate += clock.restart();
		if (timeSinceLastUpdate > timePerFrame)
		{
			update(timeSinceLastUpdate.asMilliseconds());
			timeSinceLastUpdate = sf::Time::Zero;
		}

        draw();
    }
}

void Game::update(sf::Int32 dt)
{
	ParticleManager::instance()->update();
	Grid::instance()->update();
	m_screenManager.update(m_xboxController, dt);
}

void Game::draw()
{
	m_renderTexture.clear();
	Grid::instance()->draw(m_renderTexture);
	ParticleManager::instance()->draw(m_renderTexture);
	m_screenManager.draw(m_renderTexture);
	m_renderTexture.display();

    m_window.clear();
	m_window.setView(m_view);
	m_bloom.apply(m_renderTexture.getTexture(), m_window);
    m_window.display();
}