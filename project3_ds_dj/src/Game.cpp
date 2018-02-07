#include "Game.h"
#include "ImageIcon.h"

Game::Game() :
	m_windowSettings(),
	m_xboxController(CONTROLLER_ONE),
	m_view(sf::FloatRect(0, 0, 1920, 1080)),
	m_window(sf::VideoMode::getDesktopMode(), "      Project 3 - Darren & D.J", sf::Style::Default, m_windowSettings),
	m_bloom(m_window.getSize(), 0.0f, 1.0f)
{
	std::cout << "openGL version:" << m_window.getSettings().majorVersion 
		<< "." << m_window.getSettings().minorVersion << std::endl << std::endl;

	m_windowTitle = "      Project 3 - Darren & D.J";
	m_view.zoom(1.0f);
	m_window.setMouseCursorVisible(false);
	m_window.setIcon(icon_image.width, icon_image.height, icon_image.pixel_data);


	//-----------------Load all sounds here-----------------//
	
	//	Game music
	if (!m_music.openFromFile("Assets/Sounds/GameMusic.wav"))
	{
		std::cout << "ERROR::Game::music not loaded";
	}
	m_musicPlaying = true;
	m_music.setVolume(100);
	m_music.setLoop(true);
	m_music.play();

	//	Confirm Sound
	if (!m_confirmBuffer.loadFromFile("Assets/Sounds/MenuSelect.wav"))
	{
		std::cout << "ERROR::Game:confirmBuffer not loaded";
	}
	m_confirmSound.setBuffer(m_confirmBuffer);
	m_confirmSound.setVolume(100);

	//	Pick-Up Sound
	if (!m_pickUpSoundBuffer.loadFromFile("Assets/Sounds/PickUp.wav"))
	{
		std::cout << "ERROR::Game:PickUp sound didn't load" << std::endl;
	}
	m_pickUpSound.setBuffer(m_pickUpSoundBuffer);
	m_pickUpSound.setVolume(100);

	//	Wave Complete Sound
	if (!m_waveCompleteSoundBuffer.loadFromFile("Assets/Sounds/WaveCompleteSound.wav"))
	{
		std::cout << "ERROR::Game:WaveCompleteSound didn't load" << std::endl;
	}
	m_waveCompleteSound.setBuffer(m_waveCompleteSoundBuffer);
	m_waveCompleteSound.setVolume(100);

	//	Death Sound
	if (!m_deathSoundBuffer.loadFromFile("Assets/Sounds/DeathSound.wav"))
	{
		std::cout << "ERROR::Game:DeathSound not loaded" << std::endl;
	}
	m_deathSound.setBuffer(m_deathSoundBuffer);
	m_deathSound.setVolume(100);

	//	Shot Sound
	if (!m_shotSoundBuffer.loadFromFile("Assets/Sounds/ShotSound.wav"))
	{
		std::cout << "ERROR::Game:ShotSound not loaded" << std::endl;
	}
	m_shotSound.setBuffer(m_shotSoundBuffer);
	m_shotSound.setVolume(25);

	//	Shot Sound
	if (!m_hitWallSoundBuffer.loadFromFile("Assets/Sounds/HitWall.wav"))
	{
		std::cout << "ERROR::Game:HitWall not loaded" << std::endl;
	}
	m_hitWallSound.setBuffer(m_hitWallSoundBuffer);

	//------------------------------------------------------//

	m_screenManager.add(new SplashScreen(m_view));
	m_screenManager.add(new Credits(m_view));
	m_screenManager.add(new MainMenu(m_view, &m_confirmSound));
	m_screenManager.add(new PlayMenu(m_view, &m_confirmSound));
	exitMenu = new ExitMenu(m_view, &m_confirmSound);
	m_screenManager.add(exitMenu);
	m_options = new Options(m_view, &m_music, &m_confirmSound, &m_shotSound, &m_waveCompleteSound, &m_pickUpSound, &m_deathSound);
	m_screenManager.add(m_options);
    m_screenManager.add(new GameScreen(m_xboxController, m_view, &m_confirmSound, &m_shotSound, &m_waveCompleteSound, &m_pickUpSound, &m_deathSound, &m_hitWallSound));
	m_screenManager.add(new Leaderboard(m_view));

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
			m_window.create(sf::VideoMode::getDesktopMode(), m_windowTitle, sf::Style::Fullscreen, m_windowSettings);
			m_window.setIcon(icon_image.width, icon_image.height, icon_image.pixel_data);
			m_window.setMouseCursorVisible(false);
			m_options->m_goToFullscreenMode = false;
			m_inFullscreenMode = true;
			m_inWindowedMode = false;
		}
		else if(m_options->m_goToWindowedMode && !m_inWindowedMode)
		{
			m_window.create(sf::VideoMode::getDesktopMode(), m_windowTitle, sf::Style::Default, m_windowSettings);
			m_window.setIcon(icon_image.width, icon_image.height, icon_image.pixel_data);
			m_window.setMouseCursorVisible(false);
			m_options->m_goToWindowedMode = false;
			m_inWindowedMode = true;
			m_inFullscreenMode = false;
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