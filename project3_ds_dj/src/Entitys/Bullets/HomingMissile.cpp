#include "Entitys\Bullets\HomingMissile.h"

HomingMissile::HomingMissile(const sf::Vector2f &position, const sf::Vector2f &direction)
{
	// @refactor(darren): remove this
	if (!m_texture.loadFromFile("Assets/Bullet.png"))
	{
		std::cout << "ERROR::Bullet::Image not loaded";
	}

	m_sprite.setTexture(m_texture);
	m_sprite.setScale(sf::Vector2f(0.3f, 0.3f));
	m_sprite.setOrigin(m_sprite.getLocalBounds().width / 2.0f, m_sprite.getLocalBounds().height / 2.0f);

	m_speed = 1.0f;
	m_position = position;
	m_velocity = direction * m_speed;
	m_orientation = atan2f(m_velocity.y, m_velocity.x);
	m_sprite.setRotation((m_orientation * 180) / 3.14);
	setAlive(true);
}

void HomingMissile::Update(double dt)
{

}