#ifndef PARTICLE_H
#define PARTICLE_H

#include <SFML\Graphics.hpp>
#include "MathHelper.h"

class Particle
{
public:
	Particle(sf::Color color = sf::Color(255, 255, 255), float duration = 5.0f, sf::Vector2f velocity = sf::Vector2f(),
		sf::Vector2f position = sf::Vector2f(), float rotation = 0.0f, float scale = 1.0f);

	void update();

private:
	sf::Color m_color;
	float m_duration;
	sf::Vector2f m_velocity;
	sf::Vector2f m_position;
	float m_rotation;
	float m_scale;
};

#endif