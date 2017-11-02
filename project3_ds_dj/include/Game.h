#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Screens\ScreenManager.h"
#include "Screens\MainMenu.h"
#include "Screens\Options.h"
#include "Screens\ExitMenu.h"
#include "Screens\Credits.h"
#include "Screens\PlayMenu.h"
#include "Screens\SplashScreen.h"
#include "Screens\GameScreen.h"

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

	ScreenManager m_screenManager;
    XboxController m_xboxController;

};
#endif // !GAME_H