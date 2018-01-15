#include "Entitys\PowerUps\PowerUp.h"

PowerUp::PowerUp()
{
	if (!m_texture.loadFromFile("Assets/PowerUps/Shield_Protector.png"))
	{
		std::cout << "ERROR::Power_Up::Image not loaded";
	}

	if (!m_protectorTexture.loadFromFile("Assets/PowerUps/Shield_Protector.png"))
	{
		std::cout << "ERROR::Protector::Image not loaded";
	}

	m_position = sf::Vector2f(500.0f, 400.0f);
	m_sprite.setTexture(m_texture);
	//m_sprite.setScale(sf::Vector2f(0.7f, 0.7f));
	m_sprite.setOrigin(m_sprite.getLocalBounds().width / 2.0f, m_sprite.getLocalBounds().height / 2.0f);
	m_sprite.setPosition(m_position);

	m_protectorSprite.setTexture(m_protectorTexture);
	//m_protectorSprite.setScale(sf::Vector2f(0.9f, 0.9f));
	m_protectorSprite.setOrigin(m_protectorSprite.getLocalBounds().width / 2.0f,
		m_protectorSprite.getLocalBounds().height / 2.0f);
	m_offsetShieldPos = sf::Vector2f((m_protectorSprite.getLocalBounds().width / 4.0f),
		(m_protectorSprite.getLocalBounds().height / 4.0f));
	m_protectorSprite.setPosition(m_position - m_offsetShieldPos);

}

void PowerUp::Update(double dt)
{
	m_orientation += 0.1f * (float)dt;
	if (m_orientation >= 360.0f)
		m_orientation = 0.0f;
	else if (m_orientation <= 0.0f)
		m_orientation = 360.0f;
}

void PowerUp::Draw(sf::RenderTexture &renderTexture)
{
	m_protectorSprite.setRotation(m_orientation);
	renderTexture.draw(m_protectorSprite);
	renderTexture.draw(m_sprite);
}