/// <summary>
/// @author DJ O'Leary
/// </summary>

#ifndef BULLET_H
#define BULLET_H

#include "MathHelper.h"
#include <SFML\Graphics.hpp>
#include <iostream>

class Bullet
{
public:
	Bullet();
	~Bullet();

	void update(double dt);
	void draw(sf::RenderTexture& renderTexture);

	void setAttributes( sf::Sprite &sprite ,sf::Vector2f playerPos, sf::Vector2f rightStick);
	bool isDead();

private:
	
	sf::Sprite *m_sprite;
	sf::Vector2f m_velocity;
	sf::Vector2f m_position;
	sf::Vector2f m_movementDir;
	sf::Vector2i m_inSection;	// What section the centre of the Bullet is in.
	float m_rotation;
	float m_scale;
	float m_speed;
};

#endif // !BULLET_H