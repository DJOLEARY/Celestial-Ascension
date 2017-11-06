#ifndef POINT_MASS_H
#define POINT_MASS_H

#include <SFML\Graphics.hpp>
#include "MathHelper.h"

class PointMass
{
public:
	PointMass(sf::Vector3f &position, float inverseMass);
	void applyForce(const sf::Vector3f &force);
	void applyDamping(const float factor);
	void update();
	sf::Vector3f getPosition();
	sf::Vector3f getVelocity();

private:
	// @note(darren): Using vec3 here so i can pull grid to create ripple effect
	sf::Vector3f m_position;
	sf::Vector3f m_acceleration;
	sf::Vector3f m_velocity;
	float m_damping;
	float m_inverseMass;
};

#endif