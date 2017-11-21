#ifndef GRID_H
#define GRID_H

#include <vector>
#include <SFML\Graphics.hpp>
#include "MathHelper.h"
#include "Physics\PointMass.h"
#include "Physics\Spring.h"

class Grid
{
public:
	Grid();
	void gridInit(const sf::Rect<float> &rect, const sf::Vector2f &spacing);

	void applyDirectedForce(const sf::Vector3f &force, const sf::Vector3f &position, float radius);
	void applyImplosiveForce(float force, const sf::Vector3f &position, float radius);
	void applyExplosiveForce(float force, const sf::Vector3f &position, float radius);

	void update();
	void draw(sf::RenderTexture &texture);

private:
	std::vector<Spring> m_springs;
	PointMass *m_points;
	sf::Vector2f m_screenSize;
	sf::Vector2f m_topLeftPos, m_gridSize;
	int m_cols;
	int m_rows;

	void SetPointMass(PointMass *array, int x, int y, const PointMass &val);
	PointMass *GetPointMass(PointMass *array, int x, int y);
	sf::Vector2f toVec2(const sf::Vector3f &v);
};

#endif