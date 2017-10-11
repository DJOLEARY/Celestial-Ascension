#include <SFML/Audio.hpp>
#include "EntityManager.h"
#include "Player.h"

int main()
{
	// Create the main window
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Project 3 - Darren & D.J");

	EntityManager entityManager;
	entityManager.Add(new Player());

	// Create a graphical text to display
	sf::Font font;
	if (!font.loadFromFile("Assets/arial.ttf"))
		return EXIT_FAILURE;
	sf::Text text("Hello SFML", font, 50);

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

		entityManager.Update(0.0);

		// Clear screen
		window.clear();

		entityManager.Draw(window);

		// Draw the string
		window.draw(text);
		// Update the window
		window.display();
	}

	return EXIT_SUCCESS;
}