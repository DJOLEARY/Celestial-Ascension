#include "Enemy.h"

Enemy::Enemy(sf::Vector2f *playerPos) : 
    m_playerPos(playerPos),
    m_speed(0.25f)
{
    if (!m_texture.loadFromFile("Assets/Wanderer.png"))
        std::cout << "ERROR::Enemy::Image not loaded";

    m_position = sf::Vector2f(1920 / 2, 1080 / 2);

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
    m_position += m_velocity * (float)dt;
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
    std::cout << "Velocity : " << sf::magnitude(m_velocity) << std::endl;

    if (sf::distance(m_position, *m_playerPos) < 10.0f)
    {
        m_velocity = sf::Vector2f();
    }
    else
    {
        m_velocity = sf::normalize(*m_playerPos - m_position) * m_speed;
    }
}