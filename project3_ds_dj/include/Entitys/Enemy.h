/// <summary>
/// @author DJ O'Leary and Darren Sweeney
/// </summary>

#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"
#include "MathHelper.h"
#include <iostream>

class Enemy : public Entity
{
public:
    Enemy(sf::Vector2f *playerPos);
    ~Enemy();

    virtual void Update(double dt) override;
    virtual void Draw(sf::RenderTexture &renderTexture) override;
private:

	uint16_t m_scoreValue;
    void seekPlayer();
    sf::Vector2f *m_playerPos;
};
#endif // !ENEMY_H