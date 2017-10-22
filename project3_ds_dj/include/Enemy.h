#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"
#include <iostream>

class Enemy : public Entity
{
public:
    Enemy();    //  Enemy constructor.
    ~Enemy();   //  Enemy destructor.

    virtual void Update(double dt) override;
    virtual void Draw(sf::RenderWindow &renderWindow) override;
private:

    void seek();

    float m_speed;
};
#endif // !ENEMY_H