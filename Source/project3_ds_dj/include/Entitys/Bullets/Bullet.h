/// <summary>
/// @author DJ O'Leary & Darren Sweeney
/// </summary>

#ifndef BULLET_H
#define BULLET_H

#include "..\Entity.h"
#include "MathHelper.h"
#include <iostream>
#include "Physics\Grid.h"

class Bullet : public Entity
{
public:
	Bullet();
	Bullet(const sf::Vector2f &position, const sf::Vector2f &direction, sf::Color color, bool playerBullet);

	virtual void Update(double dt) override;
	void Draw(sf::RenderTexture& renderTexture) override;

	bool getAlive();
	void setAlive(bool alive);
	bool isPlayerBullet();

private:
	float m_scale;
	bool m_alive;
	bool m_playerBullet;
};

#endif // !BULLET_H