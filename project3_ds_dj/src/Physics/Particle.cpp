#include "Physics\Particle.h"

Particle::Particle(sf::Color color, float lifeTime, sf::Vector2f position, sf::Vector2f velocity, float rotation, float scale)
	: m_color(color), m_lifeTime(lifeTime), m_velocity(velocity), m_position(position), m_rotation(rotation), m_scale(scale)
{

}

void Particle::setAttributes(sf::Color &color, float lifeTime, sf::Vector2f &position, sf::Vector2f &velocity, float rotation, float scale)
{
	m_color = color;
	m_lifeTime = lifeTime;
	m_position = position;
	m_velocity = velocity;
	m_rotation = rotation;
	m_scale = scale;
}

bool Particle::isDead()
{
	return m_lifeTime < 0.01f;
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
	if (elapsedTime.asSeconds() > 1)
	{
		m_lifeTime -= 1;
		m_clock.restart();
	}
}

void Particle::draw(sf::RenderTexture &renderTexture)
{
	sf::RectangleShape rect;
	rect.setSize(sf::Vector2f(5.0f, 1.0f));
	rect.setScale(sf::Vector2f(m_scale, m_scale));
	rect.setRotation(m_rotation);
	rect.setPosition(m_position);

	renderTexture.draw(rect);
}