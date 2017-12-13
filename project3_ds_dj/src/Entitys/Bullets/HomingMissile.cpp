#include "Entitys\Bullets\HomingMissile.h"

HomingMissile::HomingMissile(const sf::Vector2f &position, const sf::Vector2f &direction)
{
	// @refactor(darren): remove this
	if (!m_texture.loadFromFile("Assets/missile.png"))
	{
		std::cout << "ERROR::Bullet::Image not loaded";
	}

	m_sprite.setTexture(m_texture);
	m_sprite.setScale(sf::Vector2f(0.3f, 0.3f));
	m_sprite.setOrigin(m_sprite.getLocalBounds().width / 2.0f, m_sprite.getLocalBounds().height / 2.0f);

	m_speed = 0.1f;
	m_position = position;
	m_velocity = direction * m_speed;
	m_orientation = atan2f(m_velocity.y, m_velocity.x);
	m_sprite.setRotation((m_orientation * 180) / 3.14);
	setAlive(true);


	setEnemyPosition(sf::Vector2f(10.0f, 10.0f));
}

void HomingMissile::setEnemyPosition(sf::Vector2f &pos)
{
	m_enemyPosition = pos;
}

void HomingMissile::Update(double dt)
{
	// Calculate the new position
	m_position += m_velocity * (float)dt;

	// Have the missile seek the enemy
	if (sf::distance(m_position, m_enemyPosition) < 10.0f)
	{
		m_velocity = sf::Vector2f();
	}
	else
	{
		m_velocity = sf::normalize(m_enemyPosition - m_position) * m_speed;
	}

	// 
}