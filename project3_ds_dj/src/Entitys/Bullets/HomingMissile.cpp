#include "Entitys\Bullets\HomingMissile.h"

HomingMissile::HomingMissile(const sf::Vector2f &position, const sf::Vector2f &direction, sf::Vector2f *enemyPos)
	: m_enemyPosition(*enemyPos)
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
	m_rotation = 0.0f;
	m_rotationDiff = 0.0f;
	m_targetRotation = 0.0f;
	m_position = position;
	m_orientation = atan2f(m_velocity.y, m_velocity.x);
	m_sprite.setRotation((m_orientation * 180) / 3.14);
	setAlive(true);
}

void HomingMissile::Update(double dt)
{
	if (sf::distance(m_position, m_enemyPosition) < 10.0f)
	{
		m_velocity = sf::Vector2f();
	}
	else
	{
		m_velocity = sf::normalize(m_enemyPosition - m_position) * m_speed;
	}
	m_position += m_velocity * (float)dt;
	m_orientation += 0.5f;
}