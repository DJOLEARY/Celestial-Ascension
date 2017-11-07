#ifndef GAME_GRID_H
#define GAME_GRID_H

#include "Physics\PointMass.h"
#include "Physics\Spring.h"

class GameGrid
{
public:
	GameGrid(sf::Vector2f &position, float width, float height, float numParticlesWidth, float numParcilesHeight, float springSpace);
	void draw(sf::RenderTexture &renderTexture);
	void update();

private:
	PointMass* getParticle(int x, int y);
	void makeConstraint(PointMass *p1, PointMass *p2);
	void ApplyExplosiveForce(float force, sf::Vector3f position, float radius);
	bool applyForceNow;

	std::vector<Spring> m_springs;
	std::vector<PointMass> m_pointMasses;
	float numWidth, numHeight;
};

#endif