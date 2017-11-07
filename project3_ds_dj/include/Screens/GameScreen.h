/// <summary>
/// @author DJ O'Leary
/// </summary>

#ifndef GAME_SCREEN_H
#define GAME_SCREEN_H

#include "Screen.h"
#include "EntityManager.h"
#include "Player.h"
#include "Enemy.h"
#include "Entitys\Bullet.h"

class GameScreen : public Screen
{
public:

    GameScreen(XboxController & controller);
    ~GameScreen();

    virtual void update(XboxController& controller, sf::Int32 dt) override;
    
    void render(sf::RenderWindow& window);

private:

    EntityManager m_entityManager;
	Player* m_player;
	int m_numOfBullets;
	int MAX_BULLETS = 20;

};
#endif // !GAME_SCREEN_H