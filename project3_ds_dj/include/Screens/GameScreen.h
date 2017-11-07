/// <summary>
/// @author DJ O'Leary
/// </summary>

#ifndef GAME_SCREEN_H
#define GAME_SCREEN_H

#include "Screen.h"
#include "Entitys\EntityManager.h"
#include "Entitys\Player.h"
#include "Entitys\Enemy.h"
#include "Entitys\Bullet.h"

class GameScreen : public Screen
{
public:
    GameScreen(XboxController &Controller);
    ~GameScreen();

    virtual void update(XboxController &controller, sf::Int32 dt) override;
    virtual void render(sf::RenderTexture &renderTexture) override;

private:
    EntityManager m_entityManager;
	Player *m_player;
	int m_numOfBullets;
	int MAX_BULLETS = 20;
	bool isPaused;

};
#endif // !GAME_SCREEN_H