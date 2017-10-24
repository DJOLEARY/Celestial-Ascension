#include <SFML/Audio.hpp>
#include "EntityManager.h"
#include "Player.h"
#include "GUI/GUI.h"
#include "GUI\Slider.h"
#include "GUI\Label.h"
#include "GUI\Button.h"
#include "GUI\CheckBox.h"

int main()
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Project 3 - Darren & D.J");

    EntityManager entityManager;
    entityManager.Add(new Player());

    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    const sf::Time timePerFrame = sf::seconds(1.0f / 60.0f);
    sf::Clock clock;
    timeSinceLastUpdate = clock.restart();

    Gui guiSystem;
    Slider *slider = new Slider(sf::Color(122, 12, 3, 255), sf::Color(22, 12, 3, 255),
        sf::Color(45, 72, 113, 255), sf::Vector2f(1300.0f, 300.0f), 300.0f, 50.0f);
    Label *label = new Label("This is a lable", 24, sf::Vector2f(1300, 100));

	sf::Texture buttonOneTexture, buttonTwoTexture;
	if (!buttonOneTexture.loadFromFile("Assets/PlayButton.png"))
		std::cout << "ERROR::Player::Image not loaded";

	if (!buttonTwoTexture.loadFromFile("Assets/ExitButton.png"))
		std::cout << "ERROR::Player::Image not loaded";

	Button *buttonOne = new Button(buttonOneTexture, sf::Vector2f(1300.0f, 500.0f));
	Button *buttonTwo = new Button(buttonTwoTexture, sf::Vector2f(1300.0f, 700.0f));

	CheckBox *checkBox = new CheckBox(sf::Vector2f(1300.0f, 400.0f), 
	 sf::Color(22, 187, 18), sf::Color(33, 66, 3), sf::Color(200, 40, 43));

	slider->promoteFocus();

	slider->m_up = buttonTwo;
	slider->m_down = checkBox;
	checkBox->m_up = slider;
	checkBox->m_down = buttonOne;
	buttonOne->m_up = checkBox;
	buttonOne->m_down = buttonTwo;
	buttonTwo->m_up = buttonOne;
	buttonTwo->m_down = slider;

    guiSystem.add(slider);
    guiSystem.add(label);
	guiSystem.add(buttonOne);
	guiSystem.add(buttonTwo);
	guiSystem.add(checkBox);

    // @refactor(darren): I currently have two controller, makes controller a singleton?
    XboxController xboxController(CONTROLLER_TWO);

    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window : exit
            if (event.type == sf::Event::Closed)
                window.close();
        }

        guiSystem.processInput(xboxController);

        timeSinceLastUpdate += clock.restart();
        if (timeSinceLastUpdate > timePerFrame)
        {
            entityManager.Update(timeSinceLastUpdate.asMilliseconds());
            timeSinceLastUpdate = sf::Time::Zero;
        }

        // Clear screen
        window.clear();

        entityManager.Draw(window);

        window.draw(guiSystem);
        // Update the window
        window.display();
    }

    return EXIT_SUCCESS;
}