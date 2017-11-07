#include "Grid.h"

PointMass::PointMass()
	: m_acceleration(0, 0, 0),
	m_damping(0.98f),
	m_position(sf::Vector3f()),
	m_velocity(0, 0, 0),
	m_inverseMass(0)
{
}


PointMass::PointMass(
	const sf::Vector3f&position,
	float           invMass
)
	: m_acceleration(0, 0, 0),
	m_damping(0.98f),
	m_position(position),
	m_velocity(0, 0, 0),
	m_inverseMass(invMass)
{
}


void PointMass::applyForce(
	const sf::Vector3f&force
)
{
	m_acceleration += force * m_inverseMass;
}


void PointMass::increaseDamping(
	float factor
)
{
	m_damping *= factor;
}


void PointMass::update(
	void
)
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


Spring::Spring(
	PointMass  *end1,
	PointMass  *end2,
	float       stiffness,
	float       damping
) : m_end1(end1),
m_end2(end2),
m_targetLength(distance(m_end1->m_position, m_end2->m_position) * 0.95f),
m_stiffness(stiffness),
m_damping(damping)
{
}


void Spring::update(
	void
)
{
	sf::Vector3f x = m_end1->m_position - m_end2->m_position;

	float length = sf::magnitude(x);

	if (length > m_targetLength)
	{
		x = (x / length) * (length - m_targetLength);
		sf::Vector3f dv = m_end2->m_velocity - m_end1->m_velocity;
		sf::Vector3f force = m_stiffness * x - dv * m_damping;

		m_end1->applyForce(-force);
		m_end2->applyForce(force);
	}
}


void Grid::SetPointMass(
	PointMass  *array,
	int         x,
	int         y,
	const PointMass &val
)
{
	array[y * m_cols + x] = val;
}


PointMass * Grid::GetPointMass(
	PointMass* array,
	int x,
	int y
)
{
	return &array[y * m_cols + x];
}


Grid::Grid(void)
{
	const int maxGridPoints = 600;
	sf::Vector2f gridSpacing = sf::Vector2f(sqrtf(1920 * 1080 / maxGridPoints), sqrtf(1920 * 1080 / maxGridPoints));

	gridInit(sf::Rect<float>(0, 0, 1920, 1080), gridSpacing);
}


void Grid::gridInit(const sf::Rect<float> &rect, const sf::Vector2f &spacing)
{
	m_screenSize = sf::Vector2f(1920, 1080);

	int numColumns = (int)((float)rect.width / spacing.x) + 1;
	int numRows = (int)((float)rect.height / spacing.y) + 1;

	m_points = new PointMass[numColumns * numRows];
	m_cols = numColumns;
	m_rows = numRows;

	PointMass * fixedPoints = new PointMass[numColumns * numRows];

	int column = 0, row = 0;
	for (float y = rect.location.y;
		y <= rect.location.y + rect.height;
		y += spacing.y)
	{
		for (float x = rect.location.x;
			x <= rect.location.x + rect.width;
			x += spacing.x)
		{
			SetPointMass(m_points, column, row, PointMass(sf::Vector3f(x, y, 0), 1));
			SetPointMass(fixedPoints, column, row, PointMass(sf::Vector3f(x, y, 0), 0));

			column++;
		}
		row++;
		column = 0;
	}

	// link the point masses with springs
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
}


void Grid::applyDirectedForce(
	const sf::Vector2f& force,
	const sf::Vector2f& position,
	float radius
)
{
	applyDirectedForce(sf::Vector3f(force.x, force.y, 0),
		sf::Vector3f(position.x, position.y, 0),
		radius);
}


void Grid::applyDirectedForce(
	const sf::Vector3f& force,
	const sf::Vector3f& position,
	float radius
)
{
	for (int i = 0; i < m_cols * m_rows; i++)
	{
		if (distanceSquared(m_points[i].m_position) < radius * radius)
		{
			m_points[i].applyForce(10.0f * force / (10 + distance(position, m_points[i].m_position)));
		}
	}
}


void Grid::applyImplosiveForce(
	float force,
	const sf::Vector2f& position,
	float radius
)
{
	applyImplosiveForce(force, sf::Vector3f(position.x, position.y, 0), radius);
}


void Grid::applyImplosiveForce(
	float force,
	const sf::Vector3f& position,
	float radius
)
{
	for (int i = 0; i < m_cols * m_rows; i++)
	{
		float dist2 = distanceSquared(m_points[i].m_position);
		if (dist2 < radius * radius)
		{
			m_points[i].applyForce(10.0f * force * (position - m_points[i].m_position) / (100 + dist2));
			m_points[i].increaseDamping(0.6f);
		}
	}
}


void Grid::applyExplosiveForce(
	float force,
	const sf::Vector2f& position,
	float radius
)
{
	applyExplosiveForce(force, sf::Vector3f(position.x, position.y, 0), radius);
}


void Grid::applyExplosiveForce(
	float force,
	const sf::Vector3f& position,
	float radius
)
{
	for (int i = 0; i < m_cols * m_rows; i++)
	{
		float dist2 = distanceSquared(m_points[i].m_position);
		if (dist2 < radius * radius)
		{
			m_points[i].applyForce(100 * force * (m_points[i].m_position - position) / (10000 + dist2));
			m_points[i].increaseDamping(0.6f);
		}
	}
}


void Grid::update()
{
	for (size_t i = 0; i < m_springs.size(); i++)
	{
		m_springs[i].update();
	}

	for (size_t i = 0; i < m_cols * m_rows; i++)
	{
		m_points[i].update();
	}
}


void Grid::draw()
{
	int width = m_cols;
	int height = m_rows;
	Color4f color(0.12f, 0.12f, 0.55f, 0.33f);

	for (int y = 1; y < height; y++)
	{
		for (int x = 1; x < width; x++)
		{
			sf::Vector2f left, up;
			sf::Vector2f p = toVec2(GetPointMass(m_points, x, y)->m_position);
			if (x > 1)
			{
				left = toVec2(GetPointMass(m_points, x - 1, y)->m_position);
				float thickness = (y % 3 == 1) ? 3.0f : 1.0f;

				int clampedX = (int)std::min(x + 1, width - 1);
				sf::Vector2f mid = catmullRom(toVec2(GetPointMass(m_points, x - 2, y)->m_position), left, p, toVec2(GetPointMass(m_points, clampedX, y)->m_position), 0.5f);

				if (distanceSquared(mid, (left + p) / 2.0f) > 1)
				{
					Extensions::drawLine(left, mid, color, thickness);
					Extensions::drawLine(mid, p, color, thickness);
				}
				else
				{
					Extensions::drawLine(left, p, color, thickness);
				}
			}

			if (y > 1)
			{
				up = toVec2(GetPointMass(m_points, x, y - 1)->m_position);

				float thickness = (x % 3 == 1) ? 3.0f : 1.0f;
				int clampedY = (int)std::min(y + 1, height - 1);
				sf::Vector2f mid = catmullRom(toVec2(GetPointMass(m_points, x, y - 2)->m_position), up, p, toVec2(GetPointMass(m_points, x, clampedY)->m_position), 0.5f);

				if (distanceSquared(mid, (up + p) / 2.0f) > 1)
				{
					Extensions::drawLine(up, mid, color, thickness);
					Extensions::drawLine(mid, p, color, thickness);
				}
				else
				{
					Extensions::drawLine(up, p, color, thickness);
				}
			}

			if (x > 1 && y > 1)
			{
				sf::Vector2f upLeft = toVec2(GetPointMass(m_points, x - 1, y - 1)->m_position);
				Extensions::drawLine(0.5f * (upLeft + up), 0.5f * (left + p), color, 1.0f);    // vertical line
				Extensions::drawLine(0.5f * (upLeft + left), 0.5f * (up + p), color, 1.0f);    // horizontal line
			}
		}
	}
}

sf::Vector2f Grid::toVec2(const sf::Vector3f& v)
{
	float factor = (v.z + 2000.0f) * 0.0005f;
	return (sf::Vector2f(v.x, v.y) - m_screenSize * 0.5f) * factor + m_screenSize * 0.5f;
}