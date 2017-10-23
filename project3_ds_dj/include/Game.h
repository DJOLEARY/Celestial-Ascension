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

class Game
{
public:
    Game();
    ~Game();

    void run();

private:
    void update(sf::Time deltaTime);
    void draw(sf::RenderWindow & renderWindow);

    sf::RenderWindow m_window;

    EntityManager m_entityManager;

    Gui m_guiSystem;

    // @refactor(darren): I currently have two controller, makes controller a singleton?
    XboxController m_xboxController;
};
#endif // !GAME_H