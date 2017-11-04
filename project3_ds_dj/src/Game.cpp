#include "Game.h"

Game::Game() : 
    m_window(sf::VideoMode::getDesktopMode(), "Project 3 - Darren & D.J", sf::Style::Default),
    m_xboxController(CONTROLLER_TWO),
	m_view(sf::FloatRect(0, 0, 1920, 1080)),
	bloom(m_window.getSize(), 0.2f, 0.6f)
{
	std::cout << "openGL version:" << m_window.getSettings().majorVersion 
		<< "." << m_window.getSettings().minorVersion << std::endl << std::endl;

	m_view.zoom(1.0f);
	m_window.setView(m_view);
	m_window.setMouseCursorVisible(false);

    Player* player = new Player(m_xboxController);
    m_entityManager.Add(player);
    m_entityManager.Add(new Enemy(player->getPos()));
	m_screenManager.add(new SplashScreen());
	m_screenManager.add(new MainMenu());
	m_screenManager.add(new Options());
	m_screenManager.add(new ExitMenu());
	m_screenManager.add(new Credits());
	m_screenManager.add(new PlayMenu());

	if (!m_renderTexture.create(m_window.getSize().x, m_window.getSize().y))
		std::cout << "Render texture not created" << std::endl;
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

        draw();
    }
}

void Game::update(sf::Int32 dt)
{
	m_screenManager.update(m_xboxController);
	m_entityManager.Update(dt);	
}

void Game::draw()
{
	m_renderTexture.clear();
	m_screenManager.draw(m_renderTexture);
	m_renderTexture.display();

    m_window.clear();
    m_entityManager.Draw(m_renderTexture);
	bloom.apply(m_renderTexture.getTexture(), m_window);
	m_window.display();
}