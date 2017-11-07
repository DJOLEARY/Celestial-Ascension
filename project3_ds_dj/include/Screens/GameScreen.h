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

	void checkCollisions();

	EntityManager m_entityManager;
	Player* m_player;
};
#endif // !GAME_SCREEN_H