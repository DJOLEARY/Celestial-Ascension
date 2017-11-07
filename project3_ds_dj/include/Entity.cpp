#include "Entity.h"

std::string Entity::getType()
{
	return m_type;
}

sf::Vector2f Entity::getPos()
{
	return m_position;
}