#include "EntityManager.h"

/// <summary>
/// 
/// </summary>
EntityManager::EntityManager()
{

}

/// <summary>
/// 
/// </summary>
EntityManager::~EntityManager()
{
	for (Entity *entity : m_entites)
	{
		delete entity;
	}
}

/// <summary>
/// Adds an entity to the entity manager.
/// </summary>
/// <param name="entity">The entity to add</param>
void EntityManager::Add(Entity *entity)
{
	m_entites.push_back(entity);
}

/// <summary>
/// 
/// </summary>
/// <param name="dt">Delta time of game</param>
void EntityManager::Update(sf::Int32 dt)
{
	for (Entity *entity : m_entites)
	{
		entity->Update(dt);
	}
}

/// <summary>
/// 
/// </summary>
/// <param name="window"></param>
void EntityManager::Draw(sf::RenderWindow &window)
{
	for (Entity *entity : m_entites)
	{
		entity->Draw(window);
	}
}