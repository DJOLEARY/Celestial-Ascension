#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include "Entity.h"
#include "MathHelper.h"
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

	void AddEnemy(Entity *entity);
	void SetPlayer(Entity* player);
	void Update(sf::Int32 dt);
	void Draw(sf::RenderTexture &renderTexture);

private:
	std::vector<Entity*> m_enemies;
	Entity* m_player;

	void Collision(Entity* entity1, Entity* entity2);
};

#endif