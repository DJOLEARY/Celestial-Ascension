#ifndef GAME_SCREEN_H
#define GAME_SCREEN_H

#include "Screen.h"
#include "EntityManager.h"
#include "Player.h"
#include "Enemy.h"

class GameScreen : public Screen
{
public:

    GameScreen(XboxController & controller);
    ~GameScreen();

    void update(XboxController& controller, sf::Int32 dt);
    
    void draw(sf::RenderWindow& window);

private:

    EntityManager m_entityManager;


};
#endif // !GAME_SCREEN_H