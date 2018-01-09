#include "Entitys\EntityManager.h"

/// <summary>
/// 
/// </summary>
EntityManager::EntityManager()
	: m_particleManger(sf::Rect<float>(80.0f, 70.0f, 1900.0f, 1060.0f))
{
	
}

/// <summary>
/// 
/// </summary>
EntityManager::~EntityManager()
{
	for (Entity *entity : m_enemies)
	{
		delete entity;
	}
}

void EntityManager::AddBullet(Entity *entity)
{
	m_bullets.push_back(entity);
}

/// <summary>
/// Adds Enemy to the entity manager.
/// </summary>
/// <param name="entity"></param>
void EntityManager::AddEnemy(Entity * entity)
{
	m_enemies.push_back(entity);
}

void EntityManager::AddPowerUp(Entity * entity)
{
	m_powerUps.push_back(entity);
}

void EntityManager::SetPlayer(Entity * player)
{
	m_player = player;
}

/// <summary>
/// 
/// </summary>
/// <param name="dt">Delta time of game</param>
void EntityManager::Update(sf::Int32 dt)
{
	if (m_player->getAlive())
	{
		m_player->Update(dt);

		for (auto iter = m_enemies.begin(); iter != m_enemies.end(); iter++)
		{
			(*iter)->Update(dt);

			if (Collision(m_player, *iter))
			{
				m_particleManger.createExplosion(m_player->getPos(), sf::Color(216, 114, 30));
				m_player->setAlive(false);
				m_enemies.erase(iter);
				break;
			}
		}
	}

	m_particleManger.update();

	for (Entity *entity : m_powerUps)
	{
		entity->Update(dt);
	}

	for (Entity *entity : m_bullets)
	{
		entity->Update(dt);
	}

	// Check if the bullets and enemies have collided
	int count = 0;
	std::vector<int> indexesToRemove;
	for (auto iter = m_enemies.begin(); iter != m_enemies.end(); iter++)
	{
		count++;
		for (auto bulletIter = m_bullets.begin(); bulletIter != m_bullets.end(); bulletIter++)
		{
			if (Collision(*iter, *bulletIter))
			{
				indexesToRemove.push_back(count);
			}
		}
	}

	for (int index : indexesToRemove)
	{
		m_enemies.erase(m_enemies.begin() + (index - 1));
	}

	indexesToRemove.clear();
}

/// <summary>
/// 
/// </summary>
/// <param name="renderTexture"></param>
void EntityManager::Draw(sf::RenderTexture &renderTexture)
{
	for (Entity *entity : m_enemies)
	{
		entity->Draw(renderTexture);
	}

	for (Entity *entity : m_powerUps)
	{
		entity->Draw(renderTexture);
	}

	for (Entity *entity : m_bullets)
	{
		entity->Draw(renderTexture);
	}

	if (m_player->getAlive())
	{
		m_player->Draw(renderTexture);
	}

	m_particleManger.draw(renderTexture);
}

/// <summary>
/// Checks if entity2 is colliding with entity1
/// </summary>
/// <param name="entity1"></param>
/// <param name="entity2"></param>
bool EntityManager::Collision(Entity* entity1, Entity* entity2)
{
	//	Makes sure both entitys are alive.
	if (entity1->getAlive() && entity2->getAlive())
	{
		//	Cycles though the values of -1 to 1 for the x axis.
		for (int i = -1; i < 2; i++)
		{
			//	Cycles though the values of -1 to 1 for the y axis.
			for (int j = -1; j < 2; j++)
			{
				/// <summary>
				/// Checks if both entitys are in the same section.
				/// i and j are to check sections around entity 1 as parts of the sprite could protrude into other sections.
				/// </summary>
				/// <param name="entity1"></param>
				/// <param name="entity2"></param>
				if (entity1->getSection().x + i == entity2->getSection().x && entity1->getSection().y + j == entity2->getSection().y)
				{
					//	Checks the distance between the two entitys.
					if (sf::distance(entity1->getPos(), entity2->getPos()) < 20.0f)
					{
						return true;
					}
				}
			}
		}
	}

	return false;
}

std::vector<Entity*> EntityManager::GetEnemies()
{
	return m_enemies;
}

std::vector<Entity*> EntityManager::GetPowerUps()
{
	return m_powerUps;
}
