#include "Physics\PointMass.h"

PointMass::PointMass() { }

PointMass::PointMass(sf::Vector3f &position, float inverseMass)
	: m_damping(0.98f), m_position(position), m_inverseMass(inverseMass)
{

}

void PointMass::applyForce(const sf::Vector3f &force)
{
	m_acceleration += force * m_inverseMass;
}

void PointMass::applyDamping(const float factor)
{
	m_damping *= factor;
}

void PointMass::update()
{
	m_velocity += m_acceleration;
	m_position += m_velocity;
	m_acceleration = sf::Vector3f(0, 0, 0);

	if (distanceSquared(m_velocity) < 0.001f * 0.001f)
	{
		m_velocity = sf::Vector3f(0, 0, 0);
	}

	m_velocity *= m_damping;
	m_damping = 0.98f;
}

sf::Vector3f PointMass::getPosition()
{
	return m_position;
}

sf::Vector3f PointMass::getVelocity()
{
	return m_velocity;
}