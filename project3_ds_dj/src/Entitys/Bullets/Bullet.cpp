#include "Entitys\Bullets\Bullet.h"

Bullet::Bullet() { }

Bullet::Bullet(const sf::Vector2f &position, const sf::Vector2f &direction)
{
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
	m_alive = true;
}

void Bullet::Update(double dt)
{
	m_position += m_velocity * (float)dt;
	m_inSection = { (int)m_position.x / 160, (int)m_position.y / 90 };
	Grid::instance()->applyExplosiveForce(50.0f * sf::magnitude(m_velocity), sf::Vector3f(m_position.x, m_position.y, -10.0f), 120.0f);
}

void Bullet::Draw(sf::RenderTexture &renderTexture)
{
	m_sprite.setPosition(m_position);
	renderTexture.draw(m_sprite);
}

bool Bullet::getAlive()
{
	return m_alive;
}

void Bullet::setAlive(bool alive)
{
	m_alive = alive;
}