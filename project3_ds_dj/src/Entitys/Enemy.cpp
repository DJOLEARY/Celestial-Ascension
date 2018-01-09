#include "Entitys\Enemy.h"

Enemy::Enemy(sf::Vector2f *playerPos) : 
    m_playerPos(playerPos)
{
	// @refactor(darren): This should not be here. Loading a texture into memory for each enemy
	if (!m_texture.loadFromFile("Assets/Wanderer.png"))
	{
		std::cout << "ERROR::Enemy::Image not loaded";
	}

	m_alive = true;

	m_speed = 0.05f;
	m_position = sf::Vector2f(rand() % 1920, rand() % 1080);

    m_sprite.setTexture(m_texture);
    m_sprite.setScale(sf::Vector2f(0.3f, 0.3f));
    m_sprite.setOrigin(m_sprite.getLocalBounds().width / 2.0f, m_sprite.getLocalBounds().height / 2.0f);
}

Enemy::~Enemy()
{
    std::cout << "Deleting enemy" << std::endl;
}

void Enemy::Update(double dt)
{
	if (m_alive)
	{
		seekPlayer();
		m_position += m_velocity * (float)dt;
		m_orientation += 0.5f;

		m_inSection = { (int)m_position.x / 160, (int)m_position.y / 90 };
	}
}

void Enemy::Draw(sf::RenderTexture &renderTexture)
{
	if (m_alive)
	{
		m_sprite.setRotation(m_orientation);
		m_sprite.setPosition(m_position);
		renderTexture.draw(m_sprite);
	}
}

void Enemy::seekPlayer()
{
    if (sf::distance(m_position, *m_playerPos) < 10.0f)
    {
        m_velocity = sf::Vector2f();
    }
    else
    {
        m_velocity = sf::normalize(*m_playerPos - m_position) * m_speed;
    }
}