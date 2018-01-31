/// <summary>
/// @author DJ O'Leary & Darren Sweeney
/// </summary>

#ifndef GAME_SCREEN_H
#define GAME_SCREEN_H

#include "Screen.h"
#include "Entitys\EntityManager.h"
#include "Entitys\Player.h"
#include "Entitys\Enemy.h"
#include "GUI\Button.h"
#include "GUI\Label.h"
#include "HUD\HUD.h"
#include "Entitys\PowerUps\ShieldPower.h"
#include "Entitys\PowerUps\HeartPower.h"
#include "Entitys\Bullets\HomingMissile.h"

class GameScreen : public Screen
{
public:
	GameScreen(XboxController &controller, sf::View &view, sf::Sound *confirmSound, 
		sf::Sound *shotSound, sf::Sound *waveCompleteSound, sf::Sound *pickUpSound,
		sf::Sound *deathSound, sf::Sound *hitWallSound);

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
	Button *m_resume;
	Button *m_mainMenu;
	Button *m_mainMenuGameOver;
	Label *m_pauseLabel;
	Label *m_gameOverLabel;
	Button *m_retry;
	sf::Texture m_resumeTexture, m_mainMenuTexture, m_retryTexture, m_arrowTexture;
	HUD m_hud;
	uint8_t m_currentWave;
	sf::Rect<float> m_pauseBackground;
	// @refactor(darren): Put interpolation and transitionIn in the base gui
	float interpolation;
	bool transitionIn;

	sf::Vector2f m_cameraPosition;
	sf::Vector2f m_cameraVelocity;
	void cameraFollow();
	void setPauseGUIPos();
	void setGameOverGUIPos();
	void resumeButtonSelected();
	void mainMenuButtonSelected();
	void retryButtonSelected();

	bool m_leftViaPause;
	
	//	Sounds
	sf::Sound *m_confirmSound;
	sf::Sound *m_shotSound;
	sf::Sound *m_waveCompleteSound;
};
#endif // !GAME_SCREEN_H