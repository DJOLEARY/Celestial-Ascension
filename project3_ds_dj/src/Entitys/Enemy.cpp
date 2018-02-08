#include "Entitys\Enemy.h"

Enemy::Enemy(sf::Vector2f *playerPos, int randNum, sf::Sound *turretShotSound) :
	m_playerPos(playerPos),
	m_turretShotSound(turretShotSound)
{
	//	The weight chance of each enemy type
	if (randNum <= 50)
	{
		m_enemyType = EnemyType::Wanderer;
	}
	else if (randNum > 51 && randNum <= 90)
	{
		m_enemyType = EnemyType::Seeker;
	}
	else if (randNum > 91 && randNum <= 100)
	{
		m_enemyType = EnemyType::Turret;
	}

	switch (m_enemyType)
	{
	case Wanderer:

		// @refactor(darren): This should not be here. Loading a texture into memory for each enemy
		if (!m_texture.loadFromFile("Assets/Wanderer.png"))
		{
			std::cout << "ERROR::Enemy::Image not loaded";
		}

		m_speed = 0.2f;

		m_sprite.setTexture(m_texture);
		m_sprite.setScale(sf::Vector2f(0.3f, 0.3f));
		m_sprite.setOrigin(m_sprite.getLocalBounds().width / 2.0f, m_sprite.getLocalBounds().height / 2.0f);

		m_scoreValue = 100;

		break;
	case Turret:

		if (!m_texture.loadFromFile("Assets/Turret.png"))
		{
			std::cout << "ERROR::Enemy::Image not loaded";
		}

		m_speed = 0;

		m_sprite.setTexture(m_texture);
		m_sprite.setScale(sf::Vector2f(0.3f, 0.3f));
		m_sprite.setOrigin(m_sprite.getLocalBounds().width / 2.0f, m_sprite.getLocalBounds().height / 2.0f);

		m_scoreValue = 500;

		break;
	case Seeker:

		if (!m_texture.loadFromFile("Assets/Seeker.png"))
		{
			std::cout << "ERROR::Enemy::Image not loaded";
		}

		m_speed = 0.35f;

		m_sprite.setTexture(m_texture);
		m_sprite.setScale(sf::Vector2f(0.2f, 0.2f));
		m_sprite.setOrigin(m_sprite.getLocalBounds().width / 2.0f, m_sprite.getLocalBounds().height / 2.0f);

		m_scoreValue = 250;

		break;
	}

	m_alive = true;

	m_position = sf::Vector2f(rand() % (1730 - 190 + 1) + 190, rand() % (900 - 190 + 1) + 190);

	while (sf::distance(m_position, *m_playerPos) < 400.0f)
	{
		m_position = sf::Vector2f(rand() % (1730 - 190 + 1) + 190, rand() % (900 - 190 + 1) + 190);
	}
}

Enemy::~Enemy()
{
    std::cout << "Deleting enemy" << std::endl;
}

void Enemy::Update(double dt)
{
	if (m_alive)
	{
		switch (m_enemyType)
		{
		//	Regular Enemies that slowly follows the player || Enemies that are smaller and faster then regular enemies.
		case Wanderer: case Seeker:

			seekPlayer();

			m_position += m_velocity * (float)dt;

			if (m_enemyType == EnemyType::Wanderer)
			{
				m_orientation += 0.5f;
			}
			else
			{
				m_orientation += 2.0f;
			}

			break;

		//	Enemies that cannot move but can shoot at the player.
		case Turret:

			FireBullet();

			m_orientation += 0.1f;

			break;
		}

		//	Update what section the object is in for collision purposes.
		m_inSection = { (int)m_position.x / 160, (int)m_position.y / 90 };
	}
}

void Enemy::Draw(sf::RenderTexture &renderTexture)
{
	if (m_alive)
	{
		m_sprite.setRotation(m_orientation);
		m_sprite.setPosition(m_position);
		renderTexture.draw(m_sprite);
	}
}

uint16_t Enemy::getScore()
{
	return m_scoreValue;
}

EnemyType Enemy::getType()
{
	return m_enemyType;
}

void Enemy::FireBullet()
{
	if (m_enemyType == EnemyType::Turret && m_alive)
	{
		sf::Time elapsedTime = m_clock.getElapsedTime();
		if (elapsedTime.asMilliseconds() > FIRE_RATE)
		{
			m_turretShotSound->play();
			m_timeToNextShot++;
			m_clock.restart();
			m_fireBullet = true;
		}
		else
		{
			m_fireBullet = false;
		}
	}
}

void Enemy::seekPlayer()
{
	if (sf::distance(m_position, *m_playerPos) < 10.0f)
	{
		m_velocity = sf::Vector2f();
	}
	else
	{
		m_velocity = sf::normalize(*m_playerPos - m_position) * m_speed;
	}
}
