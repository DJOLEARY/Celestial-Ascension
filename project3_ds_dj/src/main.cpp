#include <SFML/Audio.hpp>
#include "EntityManager.h"
#include "Player.h"
#include "GUI/GUI.h"
#include "GUI/Slider.h"
#include "GUI\Label.h"

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
        sf::Color(2, 12, 3, 255), sf::Vector2f(100.0f, 100.0f));
    Label *label = new Label("This is a lable", 24, sf::Vector2f(400, 40));

    slider->promoteFocus();
    guiSystem.add(slider);
    guiSystem.add(label);

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