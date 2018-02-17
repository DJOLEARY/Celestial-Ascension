#include "Entitys\Enemy.h"

Enemy::Enemy(sf::Vector2f *playerPos, int randNum, sf::Sound *turretShotSound, sf::Texture *wandererTexture, sf::Texture *seekerTexture, sf::Texture *turretTexture) :
	m_playerPos(playerPos),
	m_turretShotSound(turretShotSound),
	m_color(sf::Color(255, 255, 255, 0)),
    m_wandererTexture(wandererTexture),
    m_seekerTexture(seekerTexture),
    m_turretTexture(turretTexture)
{
	//	The weight chance of each enemy type
	if (randNum <= 30)
	{
		m_enemyType = EnemyType::Wanderer;
        m_speed = 0.4f;

        m_sprite.setTexture(*m_wandererTexture);
        m_sprite.setScale(sf::Vector2f(0.3f, 0.3f));
        m_sprite.setOrigin(m_sprite.getLocalBounds().width / 2.0f, m_sprite.getLocalBounds().height / 2.0f);

        m_scoreValue = 100;
	}
	else if (randNum >= 31 && randNum <= 90)
	{
		m_enemyType = EnemyType::Seeker;
        m_speed = 0.35f;

        m_sprite.setTexture(*m_seekerTexture);
        m_sprite.setScale(sf::Vector2f(0.2f, 0.2f));
        m_sprite.setOrigin(m_sprite.getLocalBounds().width / 2.0f, m_sprite.getLocalBounds().height / 2.0f);

        m_scoreValue = 250;
	}
	else if (randNum >= 91 && randNum <= 100)
	{
		m_enemyType = EnemyType::Turret;
        m_speed = 0;

        m_sprite.setTexture(*m_turretTexture);
        m_sprite.setScale(sf::Vector2f(0.3f, 0.3f));
        m_sprite.setOrigin(m_sprite.getLocalBounds().width / 2.0f, m_sprite.getLocalBounds().height / 2.0f);

        m_scoreValue = 500;
	}

	m_alive = true;

	m_position = sf::Vector2f(rand() % (1730 - 100 + 1) + 100, rand() % (900 - 100 + 1) + 100);
    m_randPos = sf::Vector2f(rand() % (1730 - 100 + 1) + 100, rand() % (900 - 100 + 1) + 100);

	while (sf::distance(m_position, *m_playerPos) < 400.0f)
	{
		m_position = sf::Vector2f(rand() % (1730 - 100 + 1) + 100, rand() % (900 - 100 + 1) + 100);
	}
}

Enemy::~Enemy()
{
    std::cout << "Deleting enemy" << std::endl;
}

void Enemy::Update(double dt)
{
	if (m_color.a >= 250)
		m_color.a = 255;
	else
		m_color.a += 10;

	if (m_alive)
	{
        if (m_enemyType == Wanderer)
        {
            Wander();

            if (m_color.a >= 250)	// Move at full speed when fully faded in
                m_position += m_velocity * (float)dt;
            else // Move at 75% speed during fading, ease the motion on the players eyes
                m_position += m_velocity * (float)dt * 0.75f;

            m_orientation += 0.5f;
        }
        else if (m_enemyType == Seeker)
        {
            seekPlayer();

            if (m_color.a >= 250)	// Move at full speed when fully faded in
                m_position += m_velocity * (float)dt;
            else // Move at 75% speed during fading, ease the motion on the players eyes
                m_position += m_velocity * (float)dt * 0.75f;

            m_orientation += 2.0f;
        }
		//	Enemies that cannot move but can shoot at the player.
		else if ( m_enemyType == Turret)
        {
			FireBullet();

			m_orientation += 0.1f;
		}

		//	Update what section the object is in for collision purposes.
		m_inSection = { (int)m_position.x / 160, (int)m_position.y / 90 };
	}
}

void Enemy::Draw(sf::RenderTexture &renderTexture)
{
	if (m_alive)
	{
		m_sprite.setColor(m_color);
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

void Enemy::Wander()
{
    if (sf::distance(m_position, m_randPos) < 10.0f)
    {
        m_randPos = sf::Vector2f(rand() % (1730 - 100 + 1) + 100, rand() % (900 - 100 + 1) + 100);
    }
    
    m_velocity = sf::normalize(m_randPos - m_position) * m_speed;
}
