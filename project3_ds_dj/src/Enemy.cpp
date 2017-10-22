#include "Enemy.h"

Enemy::Enemy()
{
    if (!m_texture.loadFromFile("Assets/crow - black.png"))
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
    seek();
    m_sprite.setPosition(m_position);
}

void Enemy::Draw(sf::RenderWindow & renderWindow)
{
    renderWindow.draw(m_sprite);
}

void Enemy::seek()
{


}
