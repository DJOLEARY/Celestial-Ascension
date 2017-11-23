#include "Entitys/Bullet.h"

Bullet::Bullet()
{

}

Bullet::Bullet(sf::Vector2f playerPos, sf::Vector2f rightStick)
{
	m_type = EntityType::BULLET;
	m_alive = true;

	setAttributes(playerPos, rightStick);

	if (!m_texture.loadFromFile("Assets/Bullet.png"))
	{
		std::cout << "ERROR::Bullet::Image not loaded";
	}

	m_speed = 0.5f;

	m_sprite.setTexture(m_texture);
	m_sprite.setScale(sf::Vector2f(0.1f, 0.1f));
	m_sprite.setOrigin(m_sprite.getLocalBounds().width / 2.0f, m_sprite.getLocalBounds().height / 2.0f);
}

Bullet::~Bullet()
{

}

void Bullet::Update(double dt)
{
	m_position += m_velocity * (float)dt;
	m_inSection = { (int)m_position.x / 160, (int)m_position.y / 90 };

	if (m_position.x < 0 || m_position.x > 1920 || m_position.y < 0 || m_position.y > 1080)
	{
		m_alive = false;
	}
}

void Bullet::Draw(sf::RenderTexture & renderTexture)
{
	m_sprite.setPosition(m_position);
	renderTexture.draw(m_sprite);
}

void Bullet::setAttributes(sf::Vector2f playerPos, sf::Vector2f rightStick)
{
	m_position = playerPos;
	m_movementDir = rightStick;
	m_movementDir = sf::normalize(m_movementDir);
	m_orientation = (atan2(m_movementDir.y, m_movementDir.x));
	m_sprite.setRotation((m_orientation * 180) / 3.14);

	createVelocity();
}

void Bullet::createVelocity()
{
	m_velocity.x = m_speed * cos(m_orientation);
	m_velocity.y = m_speed * sin(m_orientation);
}
