#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include "Entity.h"
#include <vector>

/// <summary>
/// 
/// </summary>
class EntityManager
{
	EntityManager();
	~EntityManager();

	void Add(Entity *entity);
	void Update(double dt);
	void Draw(sf::RenderWindow &window);

private:
	std::vector<Entity*> m_entites;
};

#endif