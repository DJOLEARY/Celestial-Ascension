#include "Entitys\PowerUps\HeartPower.h"

HeartPower::HeartPower()
{
	m_type = PowerUpType::HEART_POWER;

	if (!m_texture.loadFromFile("Assets/PowerUps/Heart_Power_Up.png"))
	{
		std::cout << "ERROR::Heart_Power_Up::Image not loaded";
	}

	m_position = sf::Vector2f(500.0f, 400.0f);
	m_sprite.setTexture(m_texture);
	m_sprite.setScale(sf::Vector2f(0.7f, 0.7f));
	m_sprite.setOrigin(m_protectorSprite.getLocalBounds().width / 2.0f, m_protectorSprite.getLocalBounds().height / 2.0f);
}