#include "Game.h"

Game::Game() : 
    m_window(sf::VideoMode::getDesktopMode(), "Project 3 - Darren & D.J", sf::Style::Default),
    m_xboxController(CONTROLLER_ONE),
	m_view(sf::FloatRect(0, 0, 1920, 1080)),
	bloom(m_window.getSize(), 0.0f, 1.0f)
{
	std::cout << "openGL version:" << m_window.getSettings().majorVersion 
		<< "." << m_window.getSettings().minorVersion << std::endl << std::endl;

	m_view.zoom(1.0f);
	m_window.setView(m_view);
	m_window.setMouseCursorVisible(false);

	m_screenManager.add(new SplashScreen());
	m_screenManager.add(new MainMenu());
	m_screenManager.add(new Options());
	m_screenManager.add(new ExitMenu());
	m_screenManager.add(new Credits());
	m_screenManager.add(new PlayMenu());
    m_screenManager.add(new GameScreen(m_xboxController));

	std::cout << m_window.getSize().x << " " << m_window.getSize().y << std::endl;

	if (!m_renderTexture.create(m_view.getSize().x, m_view.getSize().y))
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
	if (m_xboxController.isButtonPressed(XBOX360_RIGHT_JOY_BUTTON))
		grid.applyImplosiveForce(50.0f, sf::Vector3f(500.0f, 500.0f, -20.0f), 100.0f);

	grid.update();
	m_screenManager.update(m_xboxController, dt);
}

void Game::draw()
{
	m_renderTexture.clear();
	m_screenManager.draw(m_renderTexture);
	grid.draw(m_renderTexture);
	sf::CircleShape circle;
	circle.setPosition(sf::Vector2f(500.0f, 500.0f));
	circle.setFillColor(sf::Color::White);
	circle.setRadius(2.0f);
	m_renderTexture.draw(circle);
	m_renderTexture.display();

    m_window.clear();
	m_screenManager.draw(m_renderTexture);
	bloom.apply(m_renderTexture.getTexture(), m_window);
    m_window.display();
}