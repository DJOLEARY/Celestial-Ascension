#ifndef PARTICLE_MANAGER_H
#define PARTICLE_MANAGER_H

#include "CircularArray.h"
#include "Particle.h"
#include <stdlib.h>
#include <iostream>

class ParticleManager
{
public:
	ParticleManager(sf::Rect<float> &m_worldBound);
	void update();
	void draw(sf::RenderTexture &renderTexture);
	void clearParticles();
	void createExplosion(sf::Vector2f &position = sf::Vector2f(), sf::Color &color = sf::Color(255, 255, 255));
	void createStream(sf::Vector2f &position = sf::Vector2f(), sf::Color &color = sf::Color(255, 255, 255));
	void createParticle(sf::Color &color, float lifeTime, sf::Vector2f &position,
		sf::Vector2f &velocity, float rotation, float scale);

private:
	typedef CircularArray<Particle> ParticleArray;
	ParticleArray m_particleArray;
	sf::Texture m_particleTexture;
	sf::Sprite m_particleSprite;
	sf::Rect<float> m_worldBound;
};

#endif