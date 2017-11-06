#include "Entitys/Bullet.h"

Bullet::Bullet(sf::Vector2f playerPos, sf::Vector2f playerVel)
{
	m_position = playerPos;
	m_velocity = playerVel;

	if (!m_texture.loadFromFile("Assets/Bullet.png"))
		std::cout << "ERROR::Bullet::Image not loaded";

	m_sprite.setTexture(m_texture);
	m_sprite.setScale(sf::Vector2f(0.3f, 0.3f));
	m_sprite.setOrigin(m_sprite.getLocalBounds().width / 2.0f, m_sprite.getLocalBounds().height / 2.0f);

}

Bullet::~Bullet()
{
}

void Bullet::Update(double dt)
{
	m_position += m_velocity * (float)dt;

	if (m_position.x < 0 || m_position.x > 1920|| m_position.y < 0|| m_position.y > 1080)
	{
		delete this;
	}
}

void Bullet::Draw(sf::RenderWindow & renderWindow)
{
	m_sprite.setPosition(m_position);
	renderWindow.draw(m_sprite);
}