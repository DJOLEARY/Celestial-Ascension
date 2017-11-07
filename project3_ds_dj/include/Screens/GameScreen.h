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

    GameScreen(XboxController & controller);
    ~GameScreen();

    virtual void update(XboxController& controller, sf::Int32 dt) override;
    
    void render(sf::RenderTexture &renderTexture);

private:

	EntityManager m_entityManager;
	Player* m_player;
	int m_numOfBullets;
	const int MAX_BULLETS = 2000;
	const float RATE_OF_FIRE = 0.5f;
	const float INPUT_THRESHOLD = 30.0f;
};
#endif // !GAME_SCREEN_H