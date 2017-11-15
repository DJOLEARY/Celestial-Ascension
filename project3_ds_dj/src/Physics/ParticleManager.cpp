#include "Physics\ParticleManager.h"

ParticleManager::ParticleManager()
	: m_particleArray(1000)
{
	srand(time(NULL));
}

void ParticleManager::update()
{
	for (uint32_t particleIndex = 0; particleIndex < m_particleArray.getCount(); particleIndex++)
	{
		Particle &particle = m_particleArray[particleIndex];

		if (particle.isDead())
			m_particleArray.decreaseCount(1);

		particle.update();
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

void ParticleManager::createExplosion(sf::Vector2f &position, sf::Color &startColor, sf::Color &targetColor)
{
	for (uint32_t i = 0; i < 100; i++)
	{
		float speed = (rand() % 10) + 2;
		float theta = sf::randF(0, 2.0f * PI);
		sf::Vector2f velocity = sf::Vector2f(speed * cos(theta), speed * sin(theta));
		float rotation = sf::radiansToDegress(theta);

		// 2. Create a color lerp so particles have different color

		createParticle(sf::Color(255, 255, 255), 2.0f, position, velocity, rotation, 2.0f);
	}
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