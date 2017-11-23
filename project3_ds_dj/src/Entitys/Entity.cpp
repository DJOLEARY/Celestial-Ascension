#include "Entitys\Entity.h"

sf::Vector2f Entity::getPos()
{
	return m_position;
}

int Entity::getType()
{
	return m_type;
}

sf::Vector2i Entity::getSection()
{
	return m_inSection;
}
