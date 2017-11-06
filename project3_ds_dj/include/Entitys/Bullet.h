/// <summary>
/// @author DJ O'Leary
/// </summary>

#ifndef BULLET_H
#define BULLET_H
#include "Entity.h"
#include <iostream>

class Bullet : public Entity
{
public:
	Bullet(sf::Vector2f playerPos, sf::Vector2f playerVel );
	~Bullet();

	virtual void Update(double dt) override;
	virtual void Draw(sf::RenderWindow& renderWindow)override;

private:
	float m_speed;

};

#endif // !BULLET_H