#include "Entitys\PowerUps\ShieldPower.h"

ShieldPower::ShieldPower()
{
	if (!m_texture.loadFromFile("Assets/PowerUps/Shield_Power_Up.png"))
	{
		std::cout << "ERROR::Shield_Power_Up::Image not loaded";
	}

	if (!m_shieldProtectorTexture.loadFromFile("Assets/PowerUps/Shield_Protector.png"))
	{
		std::cout << "ERROR::Shield_Protector::Image not loaded";
	}

	m_type = EntityType::SHIELD_POWER;

	m_position = sf::Vector2f(400.0f, 400.0f);
	m_sprite.setTexture(m_texture);
	m_sprite.setScale(sf::Vector2f(0.7f, 0.7f));
	m_sprite.setOrigin(m_sprite.getLocalBounds().width / 2.0f, m_sprite.getLocalBounds().height / 2.0f);

	m_shieldProtectorSprite.setTexture(m_shieldProtectorTexture);
	m_shieldProtectorSprite.setScale(sf::Vector2f(0.9f, 0.9f));
	m_shieldProtectorSprite.setOrigin(m_shieldProtectorSprite.getLocalBounds().width / 2.0f,
		m_shieldProtectorSprite.getLocalBounds().height / 2.0f);
}

void ShieldPower::Update(double dt)
{
	m_orientation += 0.1f * (float)dt;
	if (m_orientation >= 360.0f)
		m_orientation = 0.0f;
	else if (m_orientation <= 0.0f)
		m_orientation = 360.0f;
}

void ShieldPower::Draw(sf::RenderTexture &renderTexture)
{
	m_sprite.setPosition(m_position);
	m_shieldProtectorSprite.setPosition(m_position);
	m_shieldProtectorSprite.setRotation(m_orientation);
	renderTexture.draw(m_shieldProtectorSprite);
	renderTexture.draw(m_sprite);
}