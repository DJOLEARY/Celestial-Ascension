#include "Entitys\Entity.h"

sf::Vector2f Entity::getPos()
{
	return m_position;
}

sf::Vector2i Entity::getSection()
{
	return m_inSection;
}

sf::Sprite Entity::getSprite()
{
	return m_sprite;
}

bool Entity::getAlive()
{
	return m_alive;
}

void Entity::setAlive(bool isAlive)
{
	m_alive = isAlive;
}

bool Entity::getFireBullet()
{
	return m_fireBullet;
}
