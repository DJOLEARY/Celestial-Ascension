#ifndef PARTICLE_H
#define PARTICLE_H

#include <SFML\Graphics.hpp>
#include "MathHelper.h"

class Particle
{
public:
	Particle();
	void setAttributes(sf::Sprite &sprite, sf::Color &color, float lifeTime,
		sf::Vector2f &position, sf::Vector2f &velocity, float rotation, float scale);
	bool isDead();
	void update(sf::Rect<float> &worldBound);
	void draw(sf::RenderTexture &renderTexture);

private:
	sf::Sprite *m_sprite;
	sf::Color m_color;
	sf::Clock m_clock;
	// Life time is in seconds
	float m_lifeTime;
	int timerCounting;
	sf::Vector2f m_velocity;
	sf::Vector2f m_position;
	float m_rotation;
	float m_scale;
	float m_alphaDecreaseAmount;
};

#endif