#include "Physics\Spring.h"

Spring::Spring(PointMass *p1, PointMass *p2, float stiffness, float damping)
	: m_pointMassStart(p1), m_pointMassEnd(p2), m_stiffness(stiffness), m_damping(damping), m_targetLength(5.0f)
{

}

void Spring::update()
{
	sf::Vector3f realtiveVec = m_pointMassEnd->getPosition() - m_pointMassStart->getPosition();
	float length = sf::magnitude(realtiveVec);
	if (length <= m_targetLength)
		return;

	realtiveVec = (realtiveVec / length) * (length - m_targetLength);
	sf::Vector3f dv = m_pointMassEnd->getVelocity() - m_pointMassStart->getVelocity();
	sf::Vector3f force = m_stiffness * realtiveVec - dv * m_damping;

	m_pointMassStart->applyForce(-force);
	m_pointMassEnd->applyForce(force);
}