#include "Entitys\EntityManager.h"

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
/// <param name="renderTexture"></param>
void EntityManager::Draw(sf::RenderTexture &renderTexture)
{
	for (Entity *entity : m_entites)
	{
		entity->Draw(renderTexture);
	}
}

void EntityManager::Collisions()
{
	for (Entity *iEntity : m_entites)
	{
		for (Entity *jEntity : m_entites)
		{
			if (iEntity->getType() != jEntity->getType() || iEntity->getSection() != jEntity->getSection())
			{
				continue;
			}
			else
			{
				
			}
		}
	}
}