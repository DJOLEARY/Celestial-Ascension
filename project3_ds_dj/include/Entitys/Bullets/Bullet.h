/// <summary>
/// @author DJ O'Leary & Darren Sweeney
/// </summary>

#ifndef BULLET_H
#define BULLET_H

#include "..\Entity.h"
#include "MathHelper.h"
#include <iostream>

class Bullet : public Entity
{
public:
	Bullet();
	Bullet(const sf::Vector2f &position, const sf::Vector2f &direction);

	virtual void Update(double dt) override;
	void Draw(sf::RenderTexture& renderTexture) override;

	bool getAlive();
	void setAlive(bool alive);

private:
	float m_scale;
	bool m_alive;
};

#endif // !BULLET_H