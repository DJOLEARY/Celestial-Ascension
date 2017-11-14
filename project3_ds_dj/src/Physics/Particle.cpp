#include "Physics\Particle.h"

Particle::Particle(sf::Color color, float duration, sf::Vector2f position, sf::Vector2f velocity, float rotation, float scale)
	: m_color(color), m_duration(duration), m_velocity(velocity), m_position(position), m_rotation(rotation), m_scale(scale)
{

}

void Particle::setAttributes(sf::Color &color, float duration, sf::Vector2f &position, sf::Vector2f &velocity, float rotation, float scale)
{
	m_color = color;
	m_duration = duration;
	m_position = position;
	m_velocity = velocity;
	m_rotation = rotation;
	m_scale = scale;
}

bool Particle::isDead()
{
	return m_duration < 0;
}

void Particle::update()
{
	float speed = sf::magnitude(m_velocity);

	m_position += m_velocity * 0.0001f;

	// @refactor(darren): Leave this for testing for now
	int width = 1920;
	int height = 1080;

	if (m_position.x < 0)
	{
		m_velocity.x = (float)fabs(m_velocity.x);
	}
	else if (m_position.x > width)
	{
		m_velocity.x = (float)-fabs(m_velocity.x);
	}

	if (m_position.y < 0)
	{
		m_velocity.y = (float)fabs(m_velocity.y);
	}
	else if (m_position.x > width)
	{
		m_velocity.y = (float)-fabs(m_velocity.y);
	}

	if (fabs(m_velocity.x) + fabs(m_velocity.y) < 0.00000000001f)
	{
		m_velocity = sf::Vector2f(0.0f, 0.0f);
	}
	else
	{
		m_velocity *= 0.96f + (float)fmod(fabs(m_position.x), 0.94f);
	}

	m_lifeTime -= 1.0f / m_duration;
}

void Particle::draw(sf::RenderTexture &renderTexture)
{
	sf::RectangleShape rect;
	rect.setSize(sf::Vector2f(5.0f, 1.0f));
	rect.setRotation(m_rotation);
	rect.setPosition(m_position);

	renderTexture.draw(rect);
}