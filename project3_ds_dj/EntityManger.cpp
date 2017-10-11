#include "EntityManager.h"

EntityManager::EntityManager()
{

}

EntityManager::~EntityManager()
{

}

void EntityManager::Add(Entity *entity)
{
	m_entites.push_back(entity);
}

void EntityManager::Update(double dt)
{

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