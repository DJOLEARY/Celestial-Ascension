#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "EntityManager.h"
#include "Player.h"
#include "Enemy.h"
#include "Screens\ScreenManager.h"
#include "Screens\MainMenu.h"
#include "Screens\Options.h"
#include "Screens\ExitMenu.h"
#include "Screens\Credits.h"
#include "Screens\PlayMenu.h"

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
	ScreenManager m_screenManager;
    XboxController m_xboxController;
	MainMenu *m_mainMenu;
	Options *m_optionsMenu;
	ExitMenu *m_exitMenu;
	Credits *m_credits;
	PlayMenu *m_playMenu;

};
#endif // !GAME_H