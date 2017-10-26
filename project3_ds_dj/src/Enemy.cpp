#include "Enemy.h"

Enemy::Enemy(sf::Vector2f *playerPos) : 
    m_playerPos(playerPos),
    m_speed(2.0f)
{
    if (!m_texture.loadFromFile("Assets/Wanderer.png"))
        std::cout << "ERROR::Enemy::Image not loaded";

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
    seekPlayer();
    m_orientation += 0.5f;
}

void Enemy::Draw(sf::RenderWindow & renderWindow)
{
    m_sprite.setRotation(m_orientation);
    m_sprite.setPosition(m_position);
    renderWindow.draw(m_sprite);
}

void Enemy::seekPlayer()
{
    if (m_position.x > m_playerPos->x)
    {
        m_position.x -= m_speed;
    }
    else if (m_position.x < m_playerPos->x)
    {
        m_position.x += m_speed;
    }
    else
    {

    }

    if (m_position.y > m_playerPos->y)
    {
        m_position.y -= m_speed;
    }
    else if (m_position.y < m_playerPos->y)
    {
        m_position.y += m_speed;
    }
    else
    {

    }
}
