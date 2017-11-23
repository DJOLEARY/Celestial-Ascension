#include "Physics\Grid.h"

Grid::Grid()
{
	const int maxGridPoints = 600;
	sf::Vector2f gridSpacing = sf::Vector2f(sqrtf(1920 * 1080 / maxGridPoints), sqrtf(1920 * 1080 / maxGridPoints));

	gridInit(sf::Rect<float>(-15.0f, -15.0f, 1920, 1080), gridSpacing);
}

void Grid::gridInit(const sf::Rect<float> &rect, const sf::Vector2f &spacing)
{
	m_screenSize = sf::Vector2f(1920, 1080);

	int numColumns = (rect.width / spacing.x) + 1;
	int numRows = (rect.height / spacing.y) + 1;

	m_points = new PointMass[numColumns * numRows];
	m_cols = numColumns;
	m_rows = numRows;

	PointMass *fixedPoints = new PointMass[numColumns * numRows];

	int column = 0, row = 0;
	// @refactor(darren): Take out need for fixed points
	for (float y = rect.top; y <= rect.top + rect.height; y += spacing.y)
	{
		for (float x = rect.left; x <= rect.left + rect.width; x += spacing.x)
		{
			SetPointMass(m_points, column, row, PointMass(sf::Vector3f(x, y, 0), 1));
			SetPointMass(fixedPoints, column, row, PointMass(sf::Vector3f(x, y, 0), 0));

			column++;
		}
		row++;
		column = 0;
	}

	// @todo(darren): Might constrain each point mass on the spring perimeter so it doesn't move

	// Constrain the point masses with springs
	for (int y = 0; y < numRows; y++)
	{
		for (int x = 0; x < numColumns; x++)
		{
			if (x == 0 || y == 0 || x == numColumns - 1 || y == numRows - 1)
			{
				m_springs.push_back(Spring(GetPointMass(fixedPoints, x, y),
					GetPointMass(m_points, x, y), 0.1f, 0.1f));
			}
			else if (x % 3 == 0 && y % 3 == 0)
			{
				m_springs.push_back(Spring(GetPointMass(fixedPoints, x, y),
					GetPointMass(m_points, x, y), 0.002f, 0.02f));
			}

			if (x > 0)
			{
				m_springs.push_back(Spring(GetPointMass(m_points, x - 1, y),
					GetPointMass(m_points, x, y), 0.28f, 0.06f));
			}

			if (y > 0)
			{
				m_springs.push_back(Spring(GetPointMass(m_points, x, y - 1),
					GetPointMass(m_points, x, y), 0.28f, 0.06f));
			}
		}
	}

	m_topLeftPos = toVec2(GetPointMass(m_points, 1, 1)->getPosition());
	m_gridSize = toVec2(GetPointMass(m_points, m_cols - 2, m_rows - 2)->getPosition());
}

void Grid::applyDirectedForce(const sf::Vector3f &force, const sf::Vector3f &position, float radius)
{
	for (int i = 0; i < m_cols * m_rows; i++)
	{
		if (sf::distance(m_points[i].getPosition(), position) < radius)
		{
			m_points[i].applyForce(10.0f * force / (10 + distance(position, m_points[i].getPosition())));
		}
	}
}

void Grid::applyImplosiveForce(float force, const sf::Vector3f &position, float radius)
{
	for (int i = 0; i < m_cols * m_rows; i++)
	{
		float dist = sf::distance(m_points[i].getPosition(), position);
		if (dist < radius)
		{
			m_points[i].applyForce(10.0f * force * (position - m_points[i].getPosition()) / (100 + dist));
			m_points[i].applyDamping(0.6f);
		}
	}
}

void Grid::applyExplosiveForce(float force, const sf::Vector3f &position, float radius)
{
	for (int i = 0; i < m_cols * m_rows; i++)
	{
		float dist = sf::distance(m_points[i].getPosition(), position);
		if (dist < radius)
		{
			m_points[i].applyForce(100 * force * (m_points[i].getPosition() - position) / (10000 + dist));
			m_points[i].applyDamping(0.6f);
		}
	}
}

void Grid::update()
{
	for (size_t i = 0; i < m_springs.size(); i++)
		m_springs[i].update();

	for (size_t i = 0; i < m_cols * m_rows; i++)
		m_points[i].update();
}

void Grid::draw(sf::RenderTexture &texture)
{
	int width = m_cols;
	int height = m_rows;
	sf::Color color(0.12f * 255, 0.12f * 255, 0.55f * 255, 0.65f * 255);

	for (int y = 1; y < height; y++)
	{
		for (int x = 1; x < width; x++)
		{
			sf::Vector2f left, up;
			sf::Vector2f p = toVec2(GetPointMass(m_points, x, y)->getPosition());
			if (x > 1)
			{
				left = toVec2(GetPointMass(m_points, x - 1, y)->getPosition());
				float thickness = (y % 3 == 1) ? 3.0f : 1.0f;

				int clampedX = std::min(x + 1, width - 1);
				sf::Vector2f mid = catmullRom(toVec2(GetPointMass(m_points, x - 2, y)->getPosition()), left, p, 
					toVec2(GetPointMass(m_points, clampedX, y)->getPosition()), 0.5f);

				if (distanceSquared(mid, (left + p) / 2.0f) > 1)
				{
					sf::Vertex lineOne[] = { sf::Vertex(left, color), sf::Vertex(mid, color) };
					sf::Vertex lineTwo[] = { sf::Vertex(mid, color), sf::Vertex(p, color) };

					texture.draw(lineOne, 2, sf::Lines);
					texture.draw(lineTwo, 2, sf::Lines);
				}
				else
				{
					sf::Vertex line[] = { sf::Vertex(left, color), sf::Vertex(p, color) };

					texture.draw(line, 2, sf::Lines);
				}
			}

			if (y > 1)
			{
				up = toVec2(GetPointMass(m_points, x, y - 1)->getPosition());

				float thickness = (x % 3 == 1) ? 3.0f : 1.0f;
				int clampedY = std::min(y + 1, height - 1);
				sf::Vector2f mid = catmullRom(toVec2(GetPointMass(m_points, x, y - 2)->getPosition()), up, p,
					toVec2(GetPointMass(m_points, x, clampedY)->getPosition()), 0.5f);

				if (distanceSquared(mid, (up + p) / 2.0f) > 1)
				{
					sf::Vertex lineOne[] = { sf::Vertex(up, color), sf::Vertex(mid, color) };
					sf::Vertex lineTwo[] = { sf::Vertex(mid, color), sf::Vertex(p, color) };

					texture.draw(lineOne, 2, sf::Lines);
					texture.draw(lineTwo, 2, sf::Lines);
				}
				else
				{
					sf::Vertex line[] = { sf::Vertex(up, color), sf::Vertex(p, color) };

					texture.draw(line, 2, sf::Lines);
				}
			}

			if (x > 1 && y > 1)
			{
				sf::Vector2f upLeft = toVec2(GetPointMass(m_points, x - 1, y - 1)->getPosition());
				sf::Vertex lineOne[] = { sf::Vertex(0.5f * (upLeft + up), color), sf::Vertex(0.5f * (left + p), color) };
				sf::Vertex lineTwo[] = { sf::Vertex(0.5f * (upLeft + left), color), sf::Vertex(0.5f * (up + p), color) };

				texture.draw(lineOne, 2, sf::Lines);
				texture.draw(lineTwo, 2, sf::Lines);
			}
		}
	}


	sf::RectangleShape rectShape;
	// Top
	rectShape.setFillColor(sf::Color(61, 17, 89));
	rectShape.setPosition(m_topLeftPos);
	rectShape.setSize(sf::Vector2f(m_gridSize.x, 20.0f));
	texture.draw(rectShape);
	// Left
	rectShape.setPosition(m_topLeftPos);
	rectShape.setSize(sf::Vector2f(20.0f, m_gridSize.y));
	texture.draw(rectShape);
	// Right
	rectShape.setPosition(m_topLeftPos + sf::Vector2f(m_gridSize.x, 0.0f));
	rectShape.setSize(sf::Vector2f(20.0f, m_gridSize.y));
	texture.draw(rectShape);
	// Bottom
	rectShape.setPosition(m_topLeftPos + sf::Vector2f(0.0f, m_gridSize.y));
	rectShape.setSize(sf::Vector2f(m_gridSize.x + 20.0f, 20.0f));
	texture.draw(rectShape);
}

void Grid::SetPointMass(PointMass *array, int x, int y, const PointMass &val)
{
	array[y * m_cols + x] = val;
}

PointMass *Grid::GetPointMass(PointMass* array, int x, int y)
{
	return &array[y * m_cols + x];
}

sf::Vector2f Grid::toVec2(const sf::Vector3f& v)
{
	float factor = (v.z + 2000.0f) * 0.0005f;
	return (sf::Vector2f(v.x, v.y) - m_screenSize * 0.5f) * factor + m_screenSize * 0.5f;
}