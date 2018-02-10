/// <summary>
/// @author D.J. O'Leary & Darren Sweeney
/// </summary>

#ifndef GAME_SCREEN_H
#define GAME_SCREEN_H

#include <fstream>

#include "Screen.h"
#include "Entitys\EntityManager.h"
#include "Entitys\Player.h"
#include "Entitys\Enemy.h"
#include "GUI\Button.h"
#include "GUI\Label.h"
#include "HUD\HUD.h"
#include "Entitys\PowerUps\ShieldPower.h"
#include "Entitys\PowerUps\HeartPower.h"
#include "Entitys\PowerUps\DoubleBullet.h"

class GameScreen : public Screen
{
public:
	GameScreen(XboxController &controller, sf::View &view, sf::Sound *confirmSound, 
		sf::Sound *shotSound, sf::Sound *waveCompleteSound, sf::Sound *pickUpSound,
		sf::Sound *deathSound, sf::Sound *turretShotSound, sf::Sound *hitWallSound, sf::Sound *navigateSound);

    virtual void update(XboxController &controller, sf::Int32 dt) override;
	virtual void reset() override;
    virtual void render(sf::RenderTexture &renderTexture) override;

private:
    EntityManager m_entityManager;
	Player *m_player;
	int m_maxEnemies;
	bool m_isPaused;
	bool m_isGameOver;
	void setWave(uint8_t waveNum);

	// GUI widgets
	Gui m_gameOverGui;
	Button *m_arrowButtons[6];
	Label *m_charNameLabels[3];
	uint8_t m_charNameIndex[3] = {0, 0, 0};
	const static int MAX_USER_NAME_CHARS = 38;
	std::string m_userNameChars[MAX_USER_NAME_CHARS] = { "A", "B", "C", "D", "E", "F", "G", "H", "I", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "V", "X", "Y", "Z", "1", "2", "3", "4", "5", "6", "7", "8", "9", ".", "#", "/", "*", "(", ")" };
	Button *m_resume;
	Button *m_mainMenu;
	Button *m_mainMenuGameOver;
	Label *m_pauseLabel;
	Label *m_gameOverLabel;
	Button *m_retry;
	sf::Texture m_resumeTexture, m_mainMenuTexture, m_retryTexture, m_arrowTextureUp, m_arrowTextureDown;
	HUD m_hud;
	uint8_t m_currentWave;
	sf::Rect<float> m_pauseBackground;
	// @refactor(darren): Put interpolation and transitionIn in the base gui
	float interpolation;
	bool transitionIn;

	bool m_playerWasAlive;

	sf::Vector2f m_cameraPosition;
	sf::Vector2f m_cameraVelocity;
	void spawnPowerUp();
	void cameraFollow();
	void setPauseGUIPos();
	void setGameOverGUIPos();
	void resumeButtonSelected();
	void mainMenuButtonSelected();
	void retryButtonSelected();
	void updateLeaderboard();

	bool m_leftViaPause;
	
	//	Sounds
	sf::Sound *m_confirmSound;
	sf::Sound *m_navigateSound;
	sf::Sound *m_shotSound;
	sf::Sound *m_waveCompleteSound;
	sf::Sound *m_turretShotSound;

	std::string m_readInNames[10];
	uint32_t m_readInScores[10];
};
#endif // !GAME_SCREEN_H