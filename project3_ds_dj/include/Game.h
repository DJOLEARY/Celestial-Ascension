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
#include "Screens\Leaderboard.h"
#include "Screens\SplashScreen.h"
#include "Graphics\Bloom.h"
#include "Physics\Grid.h"
#include "Screens\GameScreen.h"
#include "Physics\ParticleManager.h"

class Game
{
public:
    Game();
    void run();

private:
    void update(sf::Int32 dt);
    void draw();

	sf::ContextSettings m_windowSettings;
    sf::RenderWindow m_window;
	std::string m_windowTitle;
	sf::View m_view;
	sf::RenderTexture m_renderTexture;
	Bloom m_bloom;
	ExitMenu *exitMenu;
	Options *m_options;
	ScreenManager m_screenManager;
    XboxController m_xboxController;
	bool m_inFullscreenMode, m_inWindowedMode;
	
	sf::Music m_music;
	bool m_musicPlaying;

	sf::SoundBuffer m_confirmBuffer;
	sf::Sound m_confirmSound;

	sf::SoundBuffer m_backBuffer;
	sf::Sound m_backSound;

	sf::SoundBuffer m_toggleSoundBuffer;
	sf::Sound m_toggleSound;

	sf::SoundBuffer m_navigateBuffer;
	sf::Sound m_navigateSound;

	sf::SoundBuffer m_deathSoundBuffer;
	sf::Sound m_deathSound;

	sf::SoundBuffer m_shotSoundBuffer;
	sf::Sound m_shotSound;

	sf::SoundBuffer m_pickUpSoundBuffer;
	sf::Sound m_pickUpSound;

	sf::SoundBuffer m_waveCompleteSoundBuffer;
	sf::Sound m_waveCompleteSound;

	sf::SoundBuffer m_turretShotSoundBuffer;
	sf::Sound m_turretShotSound;

	sf::SoundBuffer m_hitWallSoundBuffer;
	sf::Sound m_hitWallSound;
};
#endif // !GAME_H