#include "Game.h"

static sf::Int32 MS_PER_UPDATE = 10.0;

Game::Game() : 
    m_window(sf::VideoMode(1920, 1080), "Project 3 - Darren & D.J"),
    m_xboxController(CONTROLLER_TWO)
{
    
    m_entityManager.Add(new Player());

    Slider *slider = new Slider(sf::Color(122, 12, 3, 255), sf::Color(22, 12, 3, 255),
        sf::Color(2, 12, 3, 255), sf::Vector2f(1300.0f, 300.0f), 300.0f, 50.0f);
    Label *label = new Label("This is a label", 24, sf::Vector2f(1300, 100));

    sf::Texture buttonOneTexture, buttonTwoTexture;
    if (!buttonOneTexture.loadFromFile("Assets/PlayButton.png"))
        std::cout << "ERROR::Player::Image not loaded";

    if (!buttonTwoTexture.loadFromFile("Assets/ExitButton.png"))
        std::cout << "ERROR::Player::Image not loaded";

    Button *buttonOne = new Button(buttonOneTexture, sf::Vector2f(1300.0f, 500.0f));
    Button *buttonTwo = new Button(buttonTwoTexture, sf::Vector2f(1300.0f, 700.0f));

    slider->promoteFocus();

    slider->m_up = buttonTwo;
    slider->m_down = buttonOne;
    buttonOne->m_up = slider;
    buttonOne->m_down = buttonTwo;
    buttonTwo->m_up = buttonOne;
    buttonTwo->m_down = slider;

    m_guiSystem.add(slider);
    m_guiSystem.add(label);
    m_guiSystem.add(buttonOne);
    m_guiSystem.add(buttonTwo);
}

Game::~Game()
{
}

void Game::run()
{
    sf::Clock clock;
    sf::Int32 lag = 0;

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

        sf::Time dt = clock.restart();

        lag += dt.asMilliseconds();

        while (lag > MS_PER_UPDATE)
        {
                update(dt);
                lag -= MS_PER_UPDATE;
        }
        update(dt);
        draw(m_window);
    }

}

void Game::update(sf::Time deltaTime)
{
    m_guiSystem.processInput(m_xboxController);
}

void Game::draw(sf::RenderWindow & renderWindow)
{
    renderWindow.clear();
    m_entityManager.Draw(m_window);
    renderWindow.draw(m_guiSystem);
    renderWindow.display();
}
