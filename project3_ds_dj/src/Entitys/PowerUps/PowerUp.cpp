#include "Entitys\PowerUps\PowerUp.h"

PowerUp::PowerUp()
{
	if (!m_texture.loadFromFile("Assets/PowerUps/square.png"))
	{
		std::cout << "ERROR::Power_Up::Image not loaded";
	}

	if (!m_protectorTexture.loadFromFile("Assets/PowerUps/Shield_Protector.png"))
	{
		std::cout << "ERROR::Protector::Image not loaded";
	}

	m_sprite.setTexture(m_texture);
	m_sprite.setOrigin(m_sprite.getLocalBounds().width / 2.0f, m_sprite.getLocalBounds().height / 2.0f);
	m_sprite.setScale(sf::Vector2f(0.7f, 0.7f));
	m_sprite.setPosition(m_position);

	m_protectorSprite.setTexture(m_protectorTexture);
	m_protectorSprite.setOrigin(m_protectorSprite.getLocalBounds().width / 2.0f,
		m_protectorSprite.getLocalBounds().height / 2.0f);
	m_protectorSprite.setPosition(m_position);

}

void PowerUp::SetPosition(sf::Vector2f &position)
{
	m_position = position;
	m_inSection = { (int)position.x / 160, (int)position.y / 90 };
	m_sprite.setPosition(position);
	m_protectorSprite.setPosition(position);
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
	if (m_alive)
	{
		m_protectorSprite.setRotation(m_orientation);
		renderTexture.draw(m_protectorSprite);
		renderTexture.draw(m_sprite);
	}
}