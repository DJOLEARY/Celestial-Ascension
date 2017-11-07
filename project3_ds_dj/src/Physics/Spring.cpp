#include "Physics\Spring.h"

Spring::Spring(PointMass *p1, PointMass *p2, float stiffness, float damping)
	: m_pointMassStart(p1), m_pointMassEnd(p2), m_stiffness(stiffness), m_damping(damping),
	m_targetLength(sf::distance(m_pointMassStart->getPosition(), m_pointMassEnd->getPosition()) * 0.95f)
{

}


void Spring::update()
{
	sf::Vector3f x = m_pointMassStart->getPosition() - m_pointMassEnd->getPosition();

	float length = sf::magnitude(x);

	if (length > m_targetLength)
	{
		x = (x / length) * (length - m_targetLength);
		sf::Vector3f dv = m_pointMassEnd->getVelocity() - m_pointMassStart->getVelocity();
		sf::Vector3f force = m_stiffness * x - dv * m_damping;

		m_pointMassStart->applyForce(-force);
		m_pointMassEnd->applyForce(force);
	}
}