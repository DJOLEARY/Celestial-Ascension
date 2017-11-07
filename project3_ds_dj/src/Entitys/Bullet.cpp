#include "Entitys/Bullet.h"

Bullet::Bullet(sf::Vector2f playerPos, float playerOrientation) : 
	m_speed(0.25)
{
	m_position = playerPos;
	m_orientation = playerOrientation;

	if (!m_texture.loadFromFile("Assets/Bullet.png"))
		std::cout << "ERROR::Bullet::Image not loaded";

	m_type = "Bullet";

	m_sprite.setTexture(m_texture);
	m_sprite.setScale(sf::Vector2f(0.3f, 0.3f));
	m_sprite.setOrigin(m_sprite.getLocalBounds().width / 2.0f, m_sprite.getLocalBounds().height / 2.0f);
	m_sprite.setRotation(m_orientation);

	createVelocity();
}

Bullet::~Bullet()
{
}

void Bullet::Update(double dt)
{
	m_position += m_velocity * (float)dt;
}

void Bullet::Draw(sf::RenderWindow & renderWindow)
{
	m_sprite.setPosition(m_position);
	renderWindow.draw(m_sprite);
}

void Bullet::createVelocity()
{
	m_velocity.x = m_speed * cos(m_orientation * DEG_TO_RADIANS);
	m_velocity.y = m_speed * sin(m_orientation * DEG_TO_RADIANS);
}
