#include "Physics\ParticleManager.h"

ParticleManager *ParticleManager::m_instance = 0;

ParticleManager::ParticleManager(sf::Rect<float> &worldBound)
	: m_particleArray(2048), m_worldBound(worldBound), m_paused(false)
{
	if (!m_particleTexture.loadFromFile("Assets/Particle.png"))
		std::cout << "Could not load particle texture" << std::endl;

	m_particleSprite.setTexture(m_particleTexture);

	srand(time(NULL));
}

void ParticleManager::update()
{
	if (!m_paused)
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
}

void ParticleManager::setPause(bool pause)
{
	m_paused = pause;
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

void ParticleManager::createExplosion(sf::Vector2f &position, sf::Color &color, uint32_t amount)
{
	for (uint32_t i = 0; i < amount; i++)
	{
		float speed = (rand() % 10) + 2;
		float theta = sf::randF(0, 2.0f * PI);
		sf::Vector2f velocity = sf::Vector2f(speed * cos(theta), speed * sin(theta));
		float rotation = sf::radiansToDegress(theta);

		createParticle(color, 1.0f, position, velocity, rotation, 0.1f);
	}
}

void ParticleManager::createStream(sf::Vector2f &position, sf::Vector2f &velocity, sf::Color &color, float dt)
{
	if (sf::magnitude(velocity) > 0.1f)
	{
		sf::Vector2f linearVel = velocity + sf::Vector2f(sf::randF(0.0f, 1.0f), sf::randF(0.0f, 1.0f));
		float angle = atan2(velocity.y, velocity.x);
		float rotation = sf::radiansToDegress(angle);

		createParticle(color, 1.0f, position, linearVel, rotation, 0.1f);
		// @note(darren): The way lifetime currently works is that it's decremented after each second so 0.1 
		// wound count as 1 second. Leave for now and maybe adjust for polish.
		createParticle(sf::Color(255, 255, 255), 0.1f, position, linearVel, rotation, 0.1f);
	}
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