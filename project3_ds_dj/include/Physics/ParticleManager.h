#ifndef PARTICLE_MANAGER_H
#define PARTICLE_MANAGER_H

#include "CircularArray.h"
#include "Particle.h"
#include <stdlib.h>
#include <iostream>

class ParticleManager
{
public:
	static ParticleManager *instance()
	{
		if (!m_instance)
			// @todo(darren): Should really have global values for these i can use in other classes
			m_instance = new ParticleManager(sf::Rect<float>(70.0f, 70.0f, 1700.0f, 1020.0f));

		return m_instance;
	}

	void update();
	void draw(sf::RenderTexture &renderTexture);
	void clearParticles();
	void createExplosion(sf::Vector2f &position = sf::Vector2f(), sf::Color &color = sf::Color(255, 255, 255));
	void createStream(sf::Vector2f &position = sf::Vector2f(), sf::Color &color = sf::Color(255, 255, 255));
	void createParticle(sf::Color &color, float lifeTime, sf::Vector2f &position,
		sf::Vector2f &velocity, float rotation, float scale);

private:
	ParticleManager(sf::Rect<float> &m_worldBound);
	static ParticleManager *m_instance;
	typedef CircularArray<Particle> ParticleArray;
	ParticleArray m_particleArray;
	sf::Texture m_particleTexture;
	sf::Sprite m_particleSprite;
	sf::Rect<float> m_worldBound;
};

#endif