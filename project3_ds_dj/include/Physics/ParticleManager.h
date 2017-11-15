#ifndef PARTICLE_MANAGER_H
#define PARTICLE_MANAGER_H

#include "..\CircularArray.h"
#include "Particle.h"
#include <stdlib.h>

class ParticleManager
{
public:
	ParticleManager();
	void update();
	void draw(sf::RenderTexture &renderTexture);
	void clearParticles();
	void createExplosion(sf::Vector2f &position = sf::Vector2f(), 
		sf::Color &startColor = sf::Color(255, 255, 255), sf::Color &targetColor = sf::Color(255, 255, 255));
	void createParticle(sf::Color &color, float duration, sf::Vector2f &position, 
		sf::Vector2f &velocity, float rotation, float scale);

private:
	typedef CircularArray<Particle> ParticleArray;
	ParticleArray m_particleArray;
};

#endif