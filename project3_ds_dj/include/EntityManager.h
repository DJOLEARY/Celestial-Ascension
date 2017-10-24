#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include "Entity.h"
#include <vector>

/// <summary>
/// Handles all game entites update and render in the game.
/// </summary>
class EntityManager
{
public:
	EntityManager();
	~EntityManager();

	void Add(Entity *entity);
	void Update(sf::Int32 dt);
	void Draw(sf::RenderWindow &window);

private:
	std::vector<Entity*> m_entites;
};

#endif