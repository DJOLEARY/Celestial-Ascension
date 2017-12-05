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

void EntityManager::RemoveDead()
{
	for (Entity *entity : m_entites)
	{
		//m_entites.erase(std::remove_if(m_entites.begin(), m_entites.end(), isDead(entity)), m_entites.end());
	}
}

/// <summary>
/// 
/// </summary>
/// <param name="dt">Delta time of game</param>
void EntityManager::Update(sf::Int32 dt)
{
	Collisions();
	RemoveDead();

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
		if (entity->getAlive())
		{
			entity->Draw(renderTexture);
		}
	}
}

void EntityManager::Collisions()
{
	for (Entity *iEntity : m_entites)
	{
		for (Entity *jEntity : m_entites)
		{
			if (iEntity->getType() == jEntity->getType() || iEntity->getSection() != jEntity->getSection() || iEntity == jEntity)
			{
				continue;
			}
			else
			{
				if (iEntity->getSprite().getGlobalBounds().intersects(jEntity->getSprite().getGlobalBounds()))
				{
					if (iEntity->getType() == EntityType::PLAYER)
					{
						iEntity->setAlive(false);
					}

					if (jEntity->getType() == EntityType::PLAYER)
					{
						jEntity->setAlive(false);
					}
				}
			}
		}
	}
}

bool EntityManager::isDead(Entity* entity)
{
	if (entity->getAlive() == false)
	{
		return true;
	}
	
	return false;
}