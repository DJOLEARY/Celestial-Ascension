#include "Entitys\EntityManager.h"
#include "Entitys\Player.h"
#include <iostream>

/// <summary>
/// 
/// </summary>
EntityManager::EntityManager()
{

	m_font = new sf::Font();
	// @todo(darren): Really need a resource manager :(
	if (!m_font->loadFromFile("Assets/Fonts/OCRAEXT.TTF"))
		std::cout << "EntityManager::font has not loaded" << std::endl;

	m_scoreText.setFont(*m_font);
	m_scoreText.setFillColor(sf::Color(226.0f, 96.0f, 9.0f));
	m_scoreText.setString("Darren");
}

/// <summary>
/// 
/// </summary>
EntityManager::~EntityManager()
{
	for (Entity *entity : m_powerUps)
		delete entity;
	for (Entity *entity : m_enemies)
		delete entity;
	for (Entity *entity : m_bullets)
		delete entity;
	delete m_player;
	delete m_font;
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
void EntityManager::Update(sf::Int32 dt, uint32_t &score)
{
	m_player->Update(dt);

	for (auto iter = m_enemies.begin(); iter != m_enemies.end(); iter++)
	{
		(*iter)->Update(dt);

		if (Collision(m_player, *iter))
		{
			m_enemies.erase(iter);
			Player *player = dynamic_cast<Player*>(m_player);
			player->setAlive(false);
			ParticleManager::instance()->createExplosion(player->getPos(), sf::Color(200, 96, 58));
			break;
		}
	}

	for (Entity *entity : m_powerUps)
	{
		entity->Update(dt);
	}

	for (Entity *entity : m_bullets)
	{
		entity->Update(dt);
	}

	for (EntityScore &entityScore : m_entityScores)
	{
		if (entityScore.displayTime > 700)
			entityScore.removeScore = true;
		else
			entityScore.displayTime += dt;
	}

	auto isDisplaying = [](EntityScore entityScore) { return entityScore.removeScore; };
	m_entityScores.erase(std::remove_if(m_entityScores.begin(), m_entityScores.end(), isDisplaying), m_entityScores.end());

	auto outOfBounds = [](Entity *entity)
	{
		// @todo(darren): I should be storing these in some global class
		bool isOutOfBounds = entity->getPos().x < 90.0f || entity->getPos().x > 1830 || 
				entity->getPos().y < 90 || entity->getPos().y > 1000;

		if (isOutOfBounds)
		{
			ParticleManager::instance()->createExplosion(entity->getPos(), sf::Color(105, 23, 137));
		}

		return isOutOfBounds;
	};

	m_bullets.erase(std::remove_if(m_bullets.begin(), m_bullets.end(), outOfBounds), m_bullets.end());

	// Check if the bullets and enemies have collided
	for (auto iter = m_enemies.begin(); iter != m_enemies.end(); iter++)
	{
		for (auto bulletIter = m_bullets.begin(); bulletIter != m_bullets.end(); bulletIter++)
		{
			if (Collision(*iter, *bulletIter))
			{
				ParticleManager::instance()->createExplosion((*iter)->getPos(), sf::Color(31, 196, 58));
				(*iter)->setAlive(false);
				(*bulletIter)->setAlive(false);
				score += 100;
				m_entityScores.push_back(EntityScore{ (*iter)->getPos(), 100 });
			}
		}
	}

	auto isAlive = [](Entity *entity) { return !entity->getAlive(); };
	m_enemies.erase(std::remove_if(m_enemies.begin(), m_enemies.end(), isAlive), m_enemies.end());
	m_bullets.erase(std::remove_if(m_bullets.begin(), m_bullets.end(), isAlive), m_bullets.end());
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

	for (EntityScore entityScore : m_entityScores)
	{
		m_scoreText.setPosition(entityScore.scoreDisplayPos);
		m_scoreText.setString(std::to_string(entityScore.score));
		renderTexture.draw(m_scoreText);
	}
}

// Checks if entity2 is colliding with entity1
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
				// Checks if both entitys are in the same section.
				// i and j are to check sections around entity 1 as parts of the sprite 
				// could protrude into other sections.
				if (entity1->getSection().x + i == entity2->getSection().x && 
					entity1->getSection().y + j == entity2->getSection().y)
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
