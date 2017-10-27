#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "EntityManager.h"
#include "Player.h"
#include "GUI/GUI.h"
#include "GUI/Slider.h"
#include "GUI/Label.h"
#include "GUI/Button.h"
#include "GUI/CheckBox.h"
#include "GUI/RadioButtons.h"

class Game
{
public:
    Game();
    ~Game();

    void run();

private:
    void update(sf::Int32 dt);
    void draw(sf::RenderWindow & renderWindow);

    sf::RenderWindow m_window;
	sf::View m_view;

    EntityManager m_entityManager;

    Gui m_guiSystem;

	// @refactor(darren): This will be in it's own screen class
	sf::Texture buttonOneTexture, buttonTwoTexture;

    XboxController m_xboxController;
};
#endif // !GAME_H