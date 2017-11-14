#include "Physics\ParticleManager.h"

ParticleManager::ParticleManager()
	: m_particleArray(500)
{

}

void ParticleManager::update()
{
	for (uint32_t particleIndex = 0; particleIndex < m_particleArray.getCount(); particleIndex++)
	{
		Particle &particle = m_particleArray[particleIndex];
		particle.update();

		if (particle.isDead())
			m_particleArray.decreaseCount(1);
	}
}

void ParticleManager::draw(sf::RenderTexture & renderTexture)
{
	for (uint32_t particleIndex = 0; particleIndex < m_particleArray.getCount(); particleIndex++)
	{
		m_particleArray[particleIndex].draw(renderTexture);
	}
}

void ParticleManager::clearParticles()
{
	m_particleArray.setCount(0);
}

void ParticleManager::createExplosion()
{
	// @todo(darren): Might create all the particle effects in the particle manager and call them
}

void ParticleManager::createParticle(sf::Color &color, float duration, sf::Vector2f &position, 
									 sf::Vector2f &velocity, float rotation, float scale)
{
	uint32_t index;

	if (m_particleArray.getCount() == m_particleArray.getCapacity())
	{
		// If at capacity, replace the oldest one
		index = 0;
	}
	else
	{
		// If not at capacity, add at the end
		index = m_particleArray.getCount();
		m_particleArray.setCount(index + 1);
	}

	Particle &ref = m_particleArray[index];
	ref.setAttributes(color, duration, position, velocity, rotation, scale);
}