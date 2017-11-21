#include "Physics\ParticleManager.h"

ParticleManager::ParticleManager(sf::Rect<float> &worldBound)
	: m_particleArray(1000), m_worldBound(worldBound)
{
	if (!m_particleTexture.loadFromFile("Assets/Particle.png"))
		std::cout << "Could not load particle texture" << std::endl;

	m_particleSprite.setTexture(m_particleTexture);

	srand(time(NULL));
}

void ParticleManager::update()
{
	uint32_t removalCount = 0;

	for (uint32_t particleIndex = 0; particleIndex < m_particleArray.getCount(); particleIndex++)
	{
		Particle &particle = m_particleArray[particleIndex];
		m_particleArray.swap(particleIndex - removalCount, particleIndex);
		particle.update(m_worldBound);

		if (particle.isDead())
			removalCount++;
	}

	m_particleArray.setCount(m_particleArray.getCount() - removalCount);
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

void ParticleManager::createExplosion(sf::Vector2f &position, sf::Color &color)
{
	for (uint32_t i = 0; i < 100; i++)
	{
		float speed = (rand() % 10) + 2;
		float theta = sf::randF(0, 2.0f * PI);
		sf::Vector2f velocity = sf::Vector2f(speed * cos(theta), speed * sin(theta));
		float rotation = sf::radiansToDegress(theta);

		createParticle(color, 1.0f, position, velocity, rotation, 0.1f);
	}
}

void ParticleManager::createStream(sf::Vector2f &position, sf::Color &color)
{
	// @todo(darren): Create a particle exhuast like stream for player and possibly for other entities.
}

void ParticleManager::createParticle(sf::Color &color, float lifeTime, sf::Vector2f &position,
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
	ref.setAttributes(m_particleSprite, color, lifeTime, position, velocity, rotation, scale);
}