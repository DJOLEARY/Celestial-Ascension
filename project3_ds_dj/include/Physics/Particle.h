#ifndef PARTICLE_H
#define PARTICLE_H

#include <SFML\Graphics.hpp>
#include "MathHelper.h"

class Particle
{
public:
	Particle(sf::Color color = sf::Color(255, 255, 255), float lifeTime = 5.0f, sf::Vector2f velocity = sf::Vector2f(),
		sf::Vector2f position = sf::Vector2f(), float rotation = 0.0f, float scale = 1.0f);

	void setAttributes(sf::Color &color, float duration, sf::Vector2f &position, sf::Vector2f &velocity, float rotation, float scale);
	bool isDead();
	void update();
	void draw(sf::RenderTexture &renderTexture);

private:
	sf::Color m_color;
	sf::Clock m_clock;
	// Life time is in seconds
	float m_lifeTime;
	sf::Vector2f m_velocity;
	sf::Vector2f m_position;
	float m_rotation;
	float m_scale;
};

#endif