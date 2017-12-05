#include "Entitys\Bullet\BulletManager.h"


BulletManager::BulletManager(sf::Rect<float> &m_worldBound, XboxController &controller) :
	m_bulletArray(1000),
	m_worldBound(m_worldBound),
	m_controller(controller)
{
	if (!m_bulletTexture.loadFromFile("Assets/Bullet.png"))
	{
		std::cout << "ERROR::Bullet::Image not loaded";
	}
	
	m_bulletSprite.setTexture(m_bulletTexture);
}

BulletManager::~BulletManager()
{
}

void BulletManager::update(double dt)
{
	if (sf::magnitude(m_controller.getRightStick()) > INPUT_THRESHOLD)
	{
		createBullet();
	}

	uint16_t removalCount = 0;

	for (uint16_t bulletIndex = 0; bulletIndex < m_bulletArray.getCount(); bulletIndex++)
	{
		Bullet &bullet = m_bulletArray[bulletIndex];
		m_bulletArray.swap(bulletIndex - removalCount, bulletIndex);
		bullet.update(dt);

		if (bullet.isDead())
		{
			removalCount++;
		}
	}

	m_bulletArray.setCount(m_bulletArray.getCount() - removalCount);
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
