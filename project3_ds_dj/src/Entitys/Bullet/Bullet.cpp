#include "Entitys/Bullet/Bullet.h"

Bullet::Bullet()
{
	
}

Bullet::~Bullet()
{

}

void Bullet::update(double dt)
{
	m_position += m_velocity * (float)dt;
	m_inSection = { (int)m_position.x / 160, (int)m_position.y / 90 };
}

void Bullet::draw(sf::RenderTexture &renderTexture)
{
	m_sprite->setPosition(m_position);
	m_sprite->setRotation((m_rotation * 180) / 3.14);
	renderTexture.draw(*m_sprite);
}

void Bullet::setAttributes(sf::Sprite &sprite, sf::Vector2f &playerPos, sf::Vector2f &rightStick)
{
	m_sprite = &sprite;
	m_position = playerPos;
	m_movementDir = rightStick;
	m_movementDir = sf::normalize(m_movementDir);
	m_rotation = (atan2(m_movementDir.y, m_movementDir.x));
	m_sprite->setScale(sf::Vector2f(0.3f, 0.3f));
	m_sprite->setOrigin(m_sprite->getLocalBounds().width / 2.0f, m_sprite->getLocalBounds().height / 2.0f);
	m_sprite->setRotation((m_rotation * 180) / 3.14);

	m_speed = 0.5f;
	m_alive = true;

	m_velocity.x = m_speed * cos(m_rotation);
	m_velocity.y = m_speed * sin(m_rotation);
}

bool Bullet::getAlive()
{
	return m_alive;
}

void Bullet::setAlive(bool alive)
{
	m_alive = alive;
}

sf::Vector2i Bullet::getSection()
{
	return m_inSection;
}

sf::Vector2f* Bullet::getPos()
{
	return &m_position;
}
