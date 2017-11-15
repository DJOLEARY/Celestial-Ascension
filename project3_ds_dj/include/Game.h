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
#include "Graphics\Bloom.h"
#include "Physics\Grid.h"
#include "Screens\GameScreen.h"
#include "Physics\ParticleManager.h"

class Game
{
public:
    Game();
    ~Game();

    void run();

private:
    void update(sf::Int32 dt);
    void draw();



	sf::Texture m_texture;
	sf::Sprite m_sprite;


	sf::ContextSettings m_windowSettings;
    sf::RenderWindow m_window;
	sf::View m_view;
	sf::RenderTexture m_renderTexture;
	Bloom m_bloom;
	Grid m_grid;

	ScreenManager m_screenManager;
	ParticleManager m_particleManger;
    XboxController m_xboxController;

};
#endif // !GAME_H