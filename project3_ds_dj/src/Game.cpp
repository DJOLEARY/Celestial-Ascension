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

	m_music.openFromFile("Assets/Sounds/GameMusic.wav");
	m_musicPlaying = true;
	m_music.setVolume(100);
	m_music.setLoop(true);
	m_music.play();

	//	Confirm Sound
	m_confirmBuffer.loadFromFile("Assets/Sounds/MenuSelect.wav");
	m_confirmSound.setBuffer(m_confirmBuffer);
	m_confirmSound.setVolume(100);

	//	Back sound
	m_backBuffer.loadFromFile("Assets/Sounds/menu_cancel.wav");
	m_backSound.setBuffer(m_backBuffer);
	m_backSound.setVolume(100);

	//	Toggle Sound
	//m_toggleSoundBuffer.loadFromFile("Assets/Sounds/options_toggle.wav");
	m_toggleSound.setBuffer(m_toggleSoundBuffer);
	m_toggleSound.setVolume(100);

	//	Confirm Sound
	m_navigateBuffer.loadFromFile("Assets/Sounds/game_select.wav");
	m_navigateSound.setBuffer(m_navigateBuffer);
	m_navigateSound.setVolume(100);

	//	Pick-Up Sound
	m_shiledSoundBuffer.loadFromFile("Assets/Sounds/PickUp.wav");
	m_shiledSound.setBuffer(m_shiledSoundBuffer);
	m_shiledSound.setVolume(100);
	m_doubleBulletBuffer.loadFromFile("Assets/Sounds/bullet_power_up.wav");
	m_doubleBulletSound.setBuffer(m_doubleBulletBuffer);
	m_doubleBulletSound.setVolume(100);
	m_heartSoundBuffer.loadFromFile("Assets/Sounds/heart_power_up.wav");
	m_heartSound.setBuffer(m_heartSoundBuffer);
	m_heartSound.setVolume(100);

	//	Wave Complete Sound
	m_waveCompleteSoundBuffer.loadFromFile("Assets/Sounds/wave_start.wav");
	m_waveCompleteSound.setBuffer(m_waveCompleteSoundBuffer);
	m_waveCompleteSound.setVolume(100);

	//	Death Sound
	m_deathSoundBuffer.loadFromFile("Assets/Sounds/DeathSound.wav");
	m_deathSound.setBuffer(m_deathSoundBuffer);
	m_deathSound.setVolume(100);

	//	Shot Sound
	m_shotSoundBuffer.loadFromFile("Assets/Sounds/ShotSound.wav");
	m_shotSound.setBuffer(m_shotSoundBuffer);
	m_shotSound.setVolume(25);

	//	Turret Shot Sound
	m_turretShotSoundBuffer.loadFromFile("Assets/Sounds/TurretShotSound.wav");
	m_turretShotSound.setBuffer(m_turretShotSoundBuffer);

	//	Hit Wall Sound
	m_hitWallSoundBuffer.loadFromFile("Assets/Sounds/HitWallSound.wav");
	m_hitWallSound.setBuffer(m_hitWallSoundBuffer);

	m_screenManager.add(new SplashScreen(m_view));
	m_screenManager.add(new Credits(m_view, &m_backSound));
	m_screenManager.add(new MainMenu(m_view, &m_confirmSound, &m_navigateSound, &m_backSound));
	m_screenManager.add(new PlayMenu(m_view, &m_confirmSound, &m_navigateSound, &m_backSound));
	exitMenu = new ExitMenu(m_view, &m_confirmSound, &m_navigateSound, &m_backSound);
	m_screenManager.add(exitMenu);
	m_options = new Options(m_view, &m_music, &m_confirmSound, &m_shotSound, &m_waveCompleteSound, &m_shiledSound, 
		&m_doubleBulletSound, &m_heartSound, &m_deathSound, &m_turretShotSound, &m_hitWallSound, &m_navigateSound, &m_backSound);
	m_screenManager.add(m_options);
    m_screenManager.add(new GameScreen(m_xboxController, m_view, &m_confirmSound, &m_shotSound, &m_waveCompleteSound, 
		&m_shiledSound, &m_doubleBulletSound, &m_heartSound, &m_deathSound, &m_turretShotSound, &m_hitWallSound, &m_navigateSound));
	m_screenManager.add(new Leaderboard(m_view, &m_backSound));

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
    while (!exitMenu->getExitState() && m_window.isOpen())
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