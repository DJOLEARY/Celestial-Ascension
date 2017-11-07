/// <summary>
/// @author DJ O'Leary & Darren Sweeney
/// </summary>

#ifndef GAME_SCREEN_H
#define GAME_SCREEN_H

#include "Screen.h"
#include "Entitys\EntityManager.h"
#include "Entitys\Player.h"
#include "Entitys\Enemy.h"
#include "Entitys\Bullet.h"
#include "GUI\Button.h"

class GameScreen : public Screen
{
public:
    GameScreen(XboxController &controller);
    ~GameScreen();

    virtual void update(XboxController &controller, sf::Int32 dt) override;
	virtual void reset() override;
    virtual void render(sf::RenderTexture &renderTexture) override;

private:
    EntityManager m_entityManager;
	Player *m_player;
	int m_numOfBullets;
	int MAX_BULLETS = 20;
	bool isPaused;

	// GUI widgets
	Button *m_resume;
	Button *m_mainMenu;
	sf::Texture m_resumeTexture, m_mainMenuTexture;

	void resumeButtonSelected();
	void mainMenuButtonSelected();
};
#endif // !GAME_SCREEN_H