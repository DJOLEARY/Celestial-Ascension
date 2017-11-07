#ifndef GRID_H
#define GRID_H

#include <vector>
#include <SFML\Graphics.hpp>
#include "MathHelper.h"

class PointMass
{
protected:
	sf::Vector3f   m_acceleration;
	float       m_damping;

public:
	sf::Vector3f   m_position;
	sf::Vector3f   m_velocity;
	float       m_inverseMass;

public:
	PointMass();
	PointMass(const sf::Vector3f&position, float invMass);

	void applyForce(const sf::Vector3f&force);
	void increaseDamping(float factor);
	void update();
};


class Spring
{
public:
	PointMass  *m_end1;
	PointMass  *m_end2;
	float       m_targetLength;
	float       m_stiffness;
	float       m_damping;

public:
	Spring(
		PointMass  *end1,
		PointMass  *end2,
		float       stiffness,
		float       damping
	);

	void update();
};


class Grid
{
public:
	std::vector<Spring> m_springs;
	PointMass          *m_points;
	sf::Vector2f        m_screenSize;
	int                 m_cols;
	int                 m_rows;

protected:
	void SetPointMass(
		PointMass *array,
		int x,
		int y,
		const PointMass &val
	);
	PointMass *GetPointMass(
		PointMass *array,
		int x,
		int y
	);

public:
	Grid();
	void gridInit(const sf::Rect<float> &rect, const sf::Vector2f &spacing);

	void applyDirectedForce(const sf::Vector2f &force, const sf::Vector2f &position, float radius);
	void applyDirectedForce(const sf::Vector3f &force, const sf::Vector3f &position, float radius);
	void applyImplosiveForce(float force, const sf::Vector2f &position, float radius);
	void applyImplosiveForce(float force, const sf::Vector3f &position, float radius);
	void applyExplosiveForce(float force, const sf::Vector2f &position, float radius);
	void applyExplosiveForce(float force, const sf::Vector3f &position, float radius);

	void update();
	void draw();

	sf::Vector2f toVec2(const sf::Vector3f&v);
};

#endif