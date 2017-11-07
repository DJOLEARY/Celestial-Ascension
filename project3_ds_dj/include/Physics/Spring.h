#ifndef SPRING_H
#define SPRING_H

#include "PointMass.h"

class Spring
{
public:
	Spring(PointMass *p1, PointMass *p2, float stiffness, float damping);
	void update();

private:
	PointMass *m_pointMassStart;
	PointMass *m_pointMassEnd;
	float m_targetLength;
	float m_stiffness;
	float m_damping;
};

#endif