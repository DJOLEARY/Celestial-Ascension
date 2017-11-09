#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include "Entity.h"
#include <vector>
#include <typeinfo>
#include <iostream>

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
	void Draw(sf::RenderTexture &renderTexture);

private:
	std::vector<Entity*> m_entites;
};

#endif