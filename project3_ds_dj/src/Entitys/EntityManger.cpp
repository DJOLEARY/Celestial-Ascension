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
EntityManager::EntityManager(int* numOfBullets)
{
	m_numOfBullets = numOfBullets;
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
	//int index = 0;
	//std::cout << *m_numOfBullets << std::endl;
	for (Entity *entity : m_entites)
	{
		entity->Update(dt);
		/*if (entity->getType() == "Bullet" && (entity->getPos().x < 0 || entity->getPos().x > 1920 || entity->getPos().y < 0 || entity->getPos().y > 1080))
		{
			m_entites.erase(m_entites.begin() + index);
			*m_numOfBullets -= 1;
		}
		else
		{
			index++;
		}*/
	}
	//std::cout << *m_numOfBullets << std::endl;
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