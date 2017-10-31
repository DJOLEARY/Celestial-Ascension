#include "Game.h"

Game::Game() : 
    m_window(sf::VideoMode::getDesktopMode(), "Project 3 - Darren & D.J"),
    m_xboxController(CONTROLLER_ONE),
	m_view(sf::FloatRect(0, 0, 1920, 1080))
{
	m_view.zoom(1.0f);
	m_window.setView(m_view);
	m_window.setMouseCursorVisible(false);

    m_entityManager.Add(new Player(m_xboxController));
	m_screenManager.add(new SplashScreen());
	m_screenManager.add(new MainMenu());
	m_screenManager.add(new Options());
	m_screenManager.add(new ExitMenu());
	m_screenManager.add(new Credits());
	m_screenManager.add(new PlayMenu());
}

Game::~Game()
{

}

void Game::run()
{
    sf::Clock clock;
    sf::Int32 lag = 0;

	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const sf::Time timePerFrame = sf::seconds(1.0f / 60.0f);
	timeSinceLastUpdate = clock.restart();

    // Start the game loop
    while (m_window.isOpen())
    {
        // Process events
        sf::Event event;
        while (m_window.pollEvent(event))
        {
            // Close window : exit
            if (event.type == sf::Event::Closed)
                m_window.close();
        }

		timeSinceLastUpdate += clock.restart();
		if (timeSinceLastUpdate > timePerFrame)
		{
			update(timeSinceLastUpdate.asMilliseconds());
			timeSinceLastUpdate = sf::Time::Zero;
		}

        draw(m_window);
    }
}

void Game::update(sf::Int32 dt)
{
	m_screenManager.update(m_xboxController);
	m_entityManager.Update(dt);	
}

void Game::draw(sf::RenderWindow & renderWindow)
{
    renderWindow.clear();
	m_screenManager.draw(m_window);
    m_entityManager.Draw(m_window);
    renderWindow.display();
}