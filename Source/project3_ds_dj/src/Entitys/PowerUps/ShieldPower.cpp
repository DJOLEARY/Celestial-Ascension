#include "Entitys\PowerUps\ShieldPower.h"

ShieldPower::ShieldPower(sf::Vector2f &position)
{
	m_type = PowerUpType::SHIELD_POWER;

	if (!m_texture.loadFromFile("Assets/PowerUps/Shield_Power_Up.png"))
	{
		std::cout << "ERROR::Shield_Protector::Image not loaded";
	}

	m_sprite.setTexture(m_texture);
	m_sprite.setOrigin(m_sprite.getLocalBounds().width / 2.0f, m_sprite.getLocalBounds().height / 2.0f);
	SetPosition(position);
}