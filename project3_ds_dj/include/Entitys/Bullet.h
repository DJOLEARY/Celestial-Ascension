/// <summary>
/// @author DJ O'Leary
/// </summary>

#ifndef BULLET_H
#define BULLET_H
#include "Entity.h"
#include <iostream>
#include "MathHelper.h"

class Bullet : public Entity
{
public:
	Bullet(sf::Vector2f playerPos, float playerOrientation);
	~Bullet();

	virtual void Update(double dt) override;
	virtual void Draw(sf::RenderWindow& renderWindow)override;

private:
	float m_speed;

	void createVelocity();
	float DEG_TO_RADIANS = 3.14159 / 180;
};

#endif // !BULLET_H