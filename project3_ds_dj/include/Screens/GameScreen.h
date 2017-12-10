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
#include "Entitys\Bullet.h"

class GameScreen : public Screen
{
public:
	GameScreen(XboxController &controller, sf::View &view);

    virtual void update(XboxController &controller, sf::Int32 dt) override;
	virtual void reset() override;
    virtual void render(sf::RenderTexture &renderTexture) override;

private:
    EntityManager m_entityManager;
	Player *m_player;
	int m_maxEnemies;

	bool isPaused;

	// GUI widgets
	Button *m_resume;
	Button *m_mainMenu;
	Label *m_pauseLabel;
	sf::Texture m_resumeTexture, m_mainMenuTexture;
	HUD m_hud;
	sf::Rect<float> m_pauseBackground;
	// @refactor(darren): Put interpolation and transitionIn in the base gui
	float interpolation;
	bool transitionIn;

	sf::Vector2f m_cameraPosition;
	sf::Vector2f m_cameraVelocity;
	void cameraFollow(sf::Int32 dt);
	void setPauseGUIPos();
	void resumeButtonSelected();
	void mainMenuButtonSelected();
};
#endif // !GAME_SCREEN_H