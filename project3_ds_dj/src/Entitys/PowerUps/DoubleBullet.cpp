#include "Entitys\PowerUps\DoubleBullet.h"

DoubleBulletPowerUp::DoubleBulletPowerUp(sf::Vector2f &position)
{
	m_type = PowerUpType::DOUBLE_BULLET_POWER;

	if (!m_texture.loadFromFile("Assets/PowerUps/Double_Power_Up.png"))
	{
		std::cout << "ERROR::Heart_Power_Up::Image not loaded";
	}

	m_sprite.setTexture(m_texture);
	m_sprite.setOrigin(m_sprite.getLocalBounds().width / 2.0f, m_sprite.getLocalBounds().height / 2.0f);
	SetPosition(position);
}