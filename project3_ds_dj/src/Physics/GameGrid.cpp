#include "Physics\GameGrid.h"

GameGrid::GameGrid(sf::Vector2f &position, float width, float height, float numParticlesWidth, float numParcilesHeight, float springSpace)
	: numWidth(numParticlesWidth), numHeight(numParcilesHeight)
{
	m_pointMasses.resize(numWidth * numHeight);

	for (int x = 0; x < numWidth; x++)
	{
		for (int y = 0; y < numHeight; y++)
		{
			sf::Vector3f pos = sf::Vector3f(width * (x / numWidth),
				height * (y / numHeight), 0);

			m_pointMasses[y * numWidth + x] = PointMass(pos, 0.1f);
		}
	}

	for (int x = 0; x < numWidth; x++)
	{
		for (int y = 0; y < numHeight; y++)
		{
			if (x < numWidth - 1)
				makeConstraint(getParticle(x, y), getParticle(x + 1, y)); // (x,y) --- (x+1,y)

			if (y < numHeight - 1)
				makeConstraint(getParticle(x, y), getParticle(x, y + 1)); // (x,y) --- (x,y+1)

			if (x < numWidth - 1 && y < numHeight - 1)
			{
				makeConstraint(getParticle(x + 1, y), getParticle(x + 1, y + 1)); // (x+1,y) --- (x,y+1)
				makeConstraint(getParticle(x, y + 1), getParticle(x + 1, y + 1)); // (x,y+1) --- (x+1,y+1)
			}
		}
	}

	// Constrain 2 point on the cloth.
	//getParticle(0, 0)->makeUnmovable();
	//getParticle(num_particles_width - 1, 0)->makeUnmovable();
}

PointMass* GameGrid::getParticle(int x, int y)
{
	return &m_pointMasses[y * numWidth + x];
}

void GameGrid::makeConstraint(PointMass *p1, PointMass *p2)
{
	m_springs.push_back(Spring(p1, p2, 0.1f, 0.1f));
}

void GameGrid::ApplyExplosiveForce(float force, sf::Vector3f position, float radius)
{
	for (PointMass &pm : m_pointMasses)
	{
		float dist2 = sf::distance(position, pm.getPosition());
		if (dist2 < radius * radius)
		{
			pm.applyForce(100 * force * (pm.getPosition() - position) / (10000 + dist2));
			pm.applyDamping(0.6f);
		}
	}
}

void GameGrid::update()
{
	ApplyExplosiveForce(10.0f, sf::Vector3f(200.0f, 400.0f, 0.0f), 10.0f);
	/*if (applyForceNow)
	{
		applyForceNow = true;
	}*/

	for (Spring spring : m_springs)
		spring.update();

	for (PointMass pm : m_pointMasses)
		pm.update();
}

sf::Vector2f ToVec2(sf::Vector3f v)
{
	// do a perspective projection
	float factor = (v.z + 2000) / 2000;
	return (sf::Vector2f(v.x, v.y) - sf::Vector2f(1920, 1080) / 2.0f) * factor + sf::Vector2f(1920, 1080) / 2.0f;
}

/*
(x,y)	    (x+1,y)   
	*-------* 
	|       | 
	|       |
	*-------*
(x,y+1)     (x+1,y+1)
*/
void GameGrid::draw(sf::RenderTexture &renderTexture)
{
	for (int x = 0; x < numWidth; x++)
	{
		for (int y = 0; y < numHeight; y++)
		{
			if (x < numWidth - 1)
			{
				//makeConstraint(getParticle(x, y)->getPosition(), getParticle(x + 1, y)); // (x,y) --- (x+1,y)
				sf::Vertex line[] =
				{
					sf::Vertex(ToVec2(getParticle(x, y)->getPosition())),
					sf::Vertex(ToVec2(getParticle(x + 1, y)->getPosition()))
				};

				renderTexture.draw(line, 2, sf::Lines);
			}

			if (y < numHeight - 1)
			{
				//makeConstraint(getParticle(x, y), getParticle(x, y + 1)); // (x,y) --- (x,y+1)
				sf::Vertex line[] =
				{
					sf::Vertex(ToVec2(getParticle(x, y)->getPosition())),
					sf::Vertex(ToVec2(getParticle(x, y + 1)->getPosition()))
				};

				renderTexture.draw(line, 2, sf::Lines);
			}

			if (x < numWidth - 1 && y < numHeight - 1)
			{
				//makeConstraint(getParticle(x + 1, y), getParticle(x + 1, y + 1)); // (x+1,y) --- (x,y+1)
				sf::Vertex line[] =
				{
					sf::Vertex(ToVec2(getParticle(x + 1, y)->getPosition())),
					sf::Vertex(ToVec2(getParticle(x + 1, y + 1)->getPosition()))
				};

				renderTexture.draw(line, 2, sf::Lines);

				//makeConstraint(getParticle(x, y + 1), getParticle(x + 1, y + 1)); // (x,y+1) --- (x+1,y+1)
				sf::Vertex line_2[] =
				{
					sf::Vertex(ToVec2(getParticle(x, y + 1)->getPosition())),
					sf::Vertex(ToVec2(getParticle(x + 1, y + 1)->getPosition()))
				};

				renderTexture.draw(line_2, 2, sf::Lines);
			}
		}
	}
}