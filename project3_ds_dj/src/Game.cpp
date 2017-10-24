#include "Game.h"

Game::Game() : 
    m_window(sf::VideoMode(1920, 1080), "Project 3 - Darren & D.J"),
    m_xboxController(CONTROLLER_ONE)
{
    m_entityManager.Add(new Player());

	Slider *slider = new Slider(sf::Color(122, 12, 3, 255), sf::Color(22, 12, 3, 255),
		sf::Color(45, 72, 113, 255), sf::Vector2f(1300.0f, 300.0f), 300.0f, 50.0f);
	Label *label = new Label("This is a label", 24, sf::Vector2f(1300, 200));

	if (!buttonOneTexture.loadFromFile("Assets/PlayButton.png"))
		std::cout << "ERROR::Player::Image not loaded";

	if (!buttonTwoTexture.loadFromFile("Assets/ExitButton.png"))
		std::cout << "ERROR::Player::Image not loaded";

	Button *buttonOne = new Button(buttonOneTexture, sf::Vector2f(1300.0f, 500.0f));
	Button *buttonTwo = new Button(buttonTwoTexture, sf::Vector2f(1300.0f, 700.0f));

	CheckBox *checkBoxOne = new CheckBox(sf::Vector2f(1250.0f, 400.0f),
		sf::Color(22, 187, 18), sf::Color(33, 66, 3), sf::Color(200, 40, 43));
	CheckBox *checkBoxTwo = new CheckBox(sf::Vector2f(1350.0f, 400.0f),
		sf::Color(22, 187, 18), sf::Color(33, 66, 3), sf::Color(200, 40, 43));

	RadioButtons *radioButtons = new RadioButtons();
	radioButtons->add(checkBoxOne);
	radioButtons->add(checkBoxTwo);

	slider->promoteFocus();

	slider->m_up = buttonTwo;
	slider->m_down = radioButtons;
	radioButtons->m_up = slider;
	radioButtons->m_down = buttonOne;
	buttonOne->m_up = radioButtons;
	buttonOne->m_down = buttonTwo;
	buttonTwo->m_up = buttonOne;
	buttonTwo->m_down = slider;

	m_guiSystem.add(slider);
	m_guiSystem.add(label);
	m_guiSystem.add(buttonOne);
	m_guiSystem.add(buttonTwo);
	m_guiSystem.add(radioButtons);
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
	m_entityManager.Update(dt);
    m_guiSystem.processInput(m_xboxController);
}

void Game::draw(sf::RenderWindow & renderWindow)
{
    renderWindow.clear();
    m_entityManager.Draw(m_window);
    renderWindow.draw(m_guiSystem);
    renderWindow.display();
}
