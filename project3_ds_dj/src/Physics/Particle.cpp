#include "Physics\Particle.h"

Particle::Particle() { }

void Particle::setAttributes(sf::Sprite &sprite, sf::Color &color, float lifeTime, sf::Vector2f &position, sf::Vector2f &velocity, float rotation, float scale)
{
	timerCounting = 0;
	m_sprite = &sprite;
	m_sprite->setOrigin(m_sprite->getLocalBounds().width / 2.0f, m_sprite->getLocalBounds().height / 2.0f);
	m_color = color;
	m_lifeTime = lifeTime;
	m_alphaDecreaseAmount = 255 / m_lifeTime;
	m_position = position;
	m_velocity = velocity;
	m_rotation = rotation;
	m_scale = scale;
	m_color.a = 255;
	m_clock.restart();
}

bool Particle::isDead()
{
	//return m_lifeTime < 0.01f;

	bool dead = timerCounting > 2;

	return dead;
}

void Particle::update()
{
	float speed = sf::magnitude(m_velocity);

	m_position += m_velocity;

	// @todo(darren): Implement collision with grid walls

	if (fabs(sf::magnitude(m_velocity)) < 0.001f)
	{
		m_velocity = sf::Vector2f(0.0f, 0.0f);
	}
	else
	{
		m_velocity *= 0.96f;
	}

	sf::Time elapsedTime = m_clock.getElapsedTime();

	// @todo(darren): Make the alpha work with the specfied time maybe?
	if (m_color.a < 5)
	{
		m_color.a = 0;
		m_lifeTime = 0.0f;
	}
	//else
		//m_color.a -= 5;

	if (elapsedTime.asSeconds() > 1)
	{
		m_lifeTime -= 1;
		timerCounting++;
		m_clock.restart();
	}
}

void Particle::draw(sf::RenderTexture &renderTexture)
{
	m_sprite->setPosition(m_position);
	m_sprite->setRotation(m_rotation);
	m_sprite->setScale(sf::Vector2f(m_scale, m_scale));
	m_sprite->setColor(m_color);

	renderTexture.draw(*m_sprite);
}