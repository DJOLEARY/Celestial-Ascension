#include "Entitys\Bullet\BulletManager.h"


BulletManager::BulletManager(sf::Rect<float> &worldBound, XboxController &controller) :
	m_bulletArray(1000),
	m_worldBound(worldBound),
	m_controller(controller)
{
	if (!m_bulletTexture.loadFromFile("Assets/Bullet.png"))
	{
		std::cout << "ERROR::Bullet::Image not loaded";
	}
	
	m_bulletSprite.setTexture(m_bulletTexture);

	m_timerCount = 0;
	m_clock.restart();
}

BulletManager::~BulletManager()
{
}

void BulletManager::update(double dt)
{
	if (sf::magnitude(m_controller.getRightStick()) > INPUT_THRESHOLD && canFire())
	{
		createBullet();
	}

	uint16_t removalCount = 0;

	for (uint16_t bulletIndex = 0; bulletIndex < m_bulletArray.getCount(); bulletIndex++)
	{
		Bullet &bullet = m_bulletArray[bulletIndex];
		m_bulletArray.swap(bulletIndex - removalCount, bulletIndex);
		bullet.update(dt);

		checkBulletAlive(&bullet);

		if (!bullet.getAlive())
		{
			removalCount++;
			std::cout << "We have removed you Mwhahaha" << std::endl;
		}
	}

	m_bulletArray.setCount(m_bulletArray.getCount() - removalCount);

	sf::Time elapsedTime = m_clock.getElapsedTime();
	if (elapsedTime.asSeconds() > 0.1)
	{
		m_timerCount++;
		m_clock.restart();
	}
}

void BulletManager::draw(sf::RenderTexture & renderTexture)
{
	for (uint16_t bulletIndex = 0; bulletIndex < m_bulletArray.getCount(); bulletIndex++)
	{
		m_bulletArray[bulletIndex].draw(renderTexture);
	}
}

void BulletManager::createBullet()
{
	uint32_t index;

	if (m_bulletArray.getCount() == m_bulletArray.getCapacity())
	{
		index = 0;	// Replace oldest bullet.
		std::cout << "Capacity hit - Reset" << std::endl;
	}
	else
	{
		index = m_bulletArray.getCount();
		m_bulletArray.setCount(index + 1);
	}

	sf::Vector2f rightStick = m_controller.getRightStick();
	Bullet &bullet = m_bulletArray[index];
	bullet.setAttributes( m_bulletSprite, *m_playerPos, rightStick);
}

void BulletManager::clearBullets()
{
	m_bulletArray.setCount(0);
}

void BulletManager::setPlayer(sf::Vector2f *playerPos)
{
	m_playerPos = playerPos;
}

void BulletManager::checkBulletAlive(Bullet* bullet)
{
	if (bullet->getPos()->x < m_worldBound.left || bullet->getPos()->x > m_worldBound.left + m_worldBound.width ||
		bullet->getPos()->y < m_worldBound.top || bullet->getPos()->y > m_worldBound.top + m_worldBound.height)
	{
		bullet->setAlive(false);
		std::cout << "Hit border - Died" << std::endl;
	}
}

void BulletManager::BulletCollision(std::vector<Entity*> entities)
{
	for (uint16_t bulletIndex = 0; bulletIndex < m_bulletArray.getCount(); bulletIndex++)
	{
		for (Entity* entity : entities)
		{
			//	Makes sure both entitys are alive.
			if (m_bulletArray[bulletIndex].getAlive() && entity->getAlive())
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
						if (m_bulletArray[bulletIndex].getSection().x + i == entity->getSection().x && m_bulletArray[bulletIndex].getSection().y + j == entity->getSection().y)
						{
							//	Checks the distance between the two entitys.
							if (sf::distance(*m_bulletArray[bulletIndex].getPos(), entity->getPos()) < 20.0f)
							{
								entity->setAlive(false);
								m_bulletArray[bulletIndex].setAlive(false);
								std::cout << "Hit enemy - Died" << std::endl;
							}
						}
					}
				}
			}
		}
	}
}

bool BulletManager::canFire()
{
	if (m_timerCount > 1)
	{
		m_timerCount = 0;
		return true;
	}

	return false;
}
