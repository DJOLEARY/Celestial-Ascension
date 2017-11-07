#include "Entitys/Bullet.h"

Bullet::Bullet(sf::Vector2f playerPos, XboxController& controller) :
	m_speed(0.25)
{
	m_position = playerPos;
	m_movementDir = controller.getRightStick();
	m_movementDir = sf::normalize(m_movementDir);
	m_orientation = (atan2(m_movementDir.y, m_movementDir.x));

	if (!m_texture.loadFromFile("Assets/Bullet.png"))
		std::cout << "ERROR::Bullet::Image not loaded";

	m_type = "Bullet";

	m_sprite.setTexture(m_texture);
	m_sprite.setScale(sf::Vector2f(0.3f, 0.3f));
	m_sprite.setOrigin(m_sprite.getLocalBounds().width / 2.0f, m_sprite.getLocalBounds().height / 2.0f);
	m_sprite.setRotation((m_orientation * 180) / 3.14);

	createVelocity();
}

Bullet::~Bullet()
{

}

void Bullet::Update(double dt)
{
	m_position += m_velocity * (float)dt;
}

void Bullet::Draw(sf::RenderTexture & renderTexture)
{
	m_sprite.setPosition(m_position);
	renderTexture.draw(m_sprite);
}

void Bullet::createVelocity()
{
	m_velocity.x = m_speed * cos(m_orientation);
	m_velocity.y = m_speed * sin(m_orientation);
}
