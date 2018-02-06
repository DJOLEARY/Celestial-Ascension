#include "Entitys\EntityManager.h"
#include "Physics\ParticleManager.h"
#include "Physics\Grid.h"
#include <iostream>

/// <summary>
/// 
/// </summary>
EntityManager::EntityManager(sf::Sound *deathSound, sf::Sound *pickUpSound, sf::Sound *hitWallSound) :
	m_deathSound(deathSound),
	m_pickUpSound(pickUpSound),
	m_hitWallSound(hitWallSound)
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
	delete m_powerUp;
	for (Entity *entity : m_enemies)
		delete entity;
	for (Entity *entity : m_bullets)
		delete entity;
	delete m_player;
	delete m_font;
}

void EntityManager::AddBullet(Bullet *entity)
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

void EntityManager::AddPowerUp(PowerUp * entity)
{
	if (m_powerUp)
		delete m_powerUp;

	m_powerUp = entity;
}

void EntityManager::SetPlayer(Player * player)
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
			m_player->setAlive(false);
			m_deathSound->play();

			m_player->m_lives--;
			ParticleManager::instance()->createExplosion(m_player->getPos(), sf::Color(200, 96, 58));
			break;
		}
	}

	if (SimpleCollision(m_player, m_powerUp))
	{
		if (m_powerUp->getAlive())
		{
			if (m_powerUp->m_type == PowerUp::PowerUpType::HEART_POWER)
			{
				sf::Vector2f pos = m_powerUp->getPos();
				ParticleManager::instance()->createExplosion(pos, sf::Color(229, 16, 172), 30);
				Grid::instance()->applyImplosiveForce(150.0f, sf::Vector3f(pos.x, pos.y, -50.0f), 100.0f);
				m_player->m_lives++;
				m_powerUp->setAlive(false);
			}
			else if (m_powerUp->m_type == PowerUp::PowerUpType::SHIELD_POWER)
			{
				// @todo(darren): Give the player abilities
				sf::Vector2f pos = m_powerUp->getPos();
				ParticleManager::instance()->createExplosion(pos, sf::Color(229, 16, 172), 30);
				Grid::instance()->applyImplosiveForce(150.0f, sf::Vector3f(pos.x, pos.y, -50.0f), 100.0f);
				m_player->m_shieldActive = true;
				m_powerUp->setAlive(false);
			}
			else if (m_powerUp->m_type == PowerUp::PowerUpType::DOUBLE_BULLET_POWER)
			{
				// @todo(darren): Give the player abilities
				m_player->setBulletType(BulletType::DOUBLE_BULLET);
				sf::Vector2f pos = m_powerUp->getPos();
				ParticleManager::instance()->createExplosion(pos, sf::Color(229, 16, 172), 30);
				Grid::instance()->applyImplosiveForce(150.0f, sf::Vector3f(pos.x, pos.y, -50.0f), 100.0f);
				m_player->m_doubleBulletActive = true;
				m_powerUp->setAlive(false);
			}

			m_pickUpSound->play();
		}
	}
	m_powerUp->Update(dt);

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
		bool isOutOfBounds = entity->getPos().x < 90.0f || entity->getPos().x > 1830.0f || 
							 entity->getPos().y < 90.0f || entity->getPos().y > 1000.0f;

		if (isOutOfBounds)
		{
			ParticleManager::instance()->createExplosion(entity->getPos(), sf::Color(105, 23, 137));
		}

		return isOutOfBounds;

	};

	m_bullets.erase(std::remove_if(m_bullets.begin(), m_bullets.end(), outOfBounds), m_bullets.end());

	if (outOfBounds(m_player))
	{
		m_player->OutOfBounds();
		m_hitWallSound->play();
	}

	// Check if the bullets and enemies have collided
	for (auto iter = m_enemies.begin(); iter != m_enemies.end(); iter++)
	{
		for (auto bulletIter = m_bullets.begin(); bulletIter != m_bullets.end(); bulletIter++)
		{
			if ((*bulletIter)->isPlayerBullet() && Collision(*iter, *bulletIter))
			{
				ParticleManager::instance()->createExplosion((*iter)->getPos(), sf::Color(31, 196, 58));
				(*iter)->setAlive(false);
				(*bulletIter)->setAlive(false);
				score += 100;
				m_entityScores.push_back(EntityScore{ (*iter)->getPos(), 100 });
			}
		}
	}

	for (auto bulletIter = m_bullets.begin(); bulletIter != m_bullets.end(); bulletIter++)
	{
		if (!(*bulletIter)->isPlayerBullet() && Collision(m_player, *bulletIter))
		{
			ParticleManager::instance()->createExplosion((m_player)->getPos(), sf::Color(31, 196, 58));
			(m_player)->m_lives--;
			m_player->setAlive(false);
			(*bulletIter)->setAlive(false);
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

	m_powerUp->Draw(renderTexture);

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

bool EntityManager::SimpleCollision(Entity* entity1, Entity* entity2)
{
	sf::Vector2f vec = entity2->getPos() - entity1->getPos();
	if (sf::magnitude(vec) < 50.0f)
		return true;

	return false;
}

std::vector<Entity*> &EntityManager::GetEnemies()
{
	return m_enemies;
}

std::vector<EntityScore> &EntityManager::GetEnemyScores()
{
	return m_entityScores;
}

int EntityManager::GetEnemiesSize()
{
	return m_enemies.size();
}

Entity *EntityManager::GetPowerUp()
{
	return m_powerUp;
}

void EntityManager::reset()
{
	m_enemies.clear();
	m_bullets.clear();
}
