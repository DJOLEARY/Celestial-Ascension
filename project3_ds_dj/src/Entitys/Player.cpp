#include "Entitys\Player.h"
#include "Physics\ParticleManager.h"
#include "Physics\Grid.h"

/// <summary>
/// 
/// </summary>
Player::Player(XboxController &controller, sf::Sound *shotSound) :
	m_xboxController(controller),
	m_lives(3), 
	m_shieldActive(false),
	m_rotationDiff(0.0f), 
	m_timeToNextShot(0),
	m_shotSound(shotSound),
	m_shieldScale(0.0f),
	m_shieldDeactive(false),
	m_timeToShieldOver(MAX_SHIELD_TIME),
	m_timeToDoubleBulletOver(MAX_BULLET_TIME)
{
	if (!m_texture.loadFromFile("Assets/PlayerShip.png"))
		std::cout << "ERROR::Player::Image ship not loaded";
	if(!m_playerShieldTexture.loadFromFile("Assets/PowerUps/player_shield.png"))
		std::cout << "ERROR::Player::Image Shield not loaded";

	m_position = sf::Vector2f(1000.0f, 500.0f);
	m_speed = 0.025f;
	m_sprite.setTexture(m_texture);
	m_sprite.setScale(0.3f, 0.3f);
	m_sprite.setOrigin(m_sprite.getLocalBounds().width / 2.0f, m_sprite.getLocalBounds().height / 2.0f);

	m_playerShieldSprite.setTexture(m_playerShieldTexture);
	m_playerShieldSprite.setPosition(m_position);
	m_playerShieldSprite.setScale(m_shieldScale, m_shieldScale);
	m_playerShieldSprite.setOrigin(m_playerShieldSprite.getLocalBounds().width  / 2.0f, 
								   m_playerShieldSprite.getLocalBounds().height / 2.0f);
}

void Player::SpawnPlayer(bool immediateSpawn)
{
	sf::Time elapsedTime = m_clock.getElapsedTime();
	if (elapsedTime.asSeconds() > TIME_TO_SPAWN || immediateSpawn)
	{
		m_alive = true;
		m_shieldActive = false;
		m_shieldScale = 0.0f;
		m_timeToShieldOver = MAX_SHIELD_TIME;
		m_timeToDoubleBulletOver = MAX_BULLET_TIME;
		m_doubleBulletActive = false;
		setBulletType(BulletType::SINGLE_BULLET);
		m_velocity = sf::Vector2f();
		m_position = sf::Vector2f(1000.0f, 500.0f);
		Grid::instance()->applyImplosiveForce(150.0f, sf::Vector3f(m_position.x, m_position.y, -50.0f), 100.0f);
		m_clock.restart();
	}
}

/// <summary>
/// Handles the controller input for the player mechanics in game.
/// </summary>
void Player::ProcessInput(double dt)
{
	if (sf::magnitude(m_xboxController.getLeftStick()) > INPUT_THRESHOLD)
	{
		m_movementDir = m_xboxController.getLeftStick();
		m_movementDir = sf::normalize(m_movementDir);
		m_targetOrientation = (atan2(m_movementDir.y, m_movementDir.x) * 180) / 3.14;
		m_velocity = m_speed * m_movementDir * (float)dt;
		m_rotationDiff = m_targetOrientation - m_orientation;
		ParticleManager::instance()->createStream(m_position, m_velocity, sf::Color(119, 2, 2), dt);
	}

	m_position += m_velocity * (float)dt;

	if (m_rotationDiff >= m_orientation + 5 && m_rotationDiff <= m_orientation - 5)
	{
		m_orientation += 1.0f;
		if (m_orientation >= 360.0f)
			m_orientation = 0.0f;
		else if (m_orientation <= 0.0f)
			m_orientation = 360.0f;
	}

	if (sf::magnitude(m_velocity) > 0.001f)
	{
		m_velocity *= 0.95f;
	}
	else if (sf::magnitude(m_velocity) < 0.001f)
	{
		m_velocity = sf::Vector2f();
	}
}

bool Player::FireBullet()
{
	// if (sf::magnitude(m_xboxController.getLeftStick()) > INPUT_THRESHOLD && m_alive)
	if (sf::magnitude(m_xboxController.getRightStick()) > INPUT_THRESHOLD && m_alive)
	{
		sf::Time elapsedTime = m_clock.getElapsedTime();
		if (elapsedTime.asMilliseconds() > FIRE_RATE)
		{
			m_shotSound->play();

			m_timeToNextShot++;
			m_clock.restart();
			return true;
		}
	}

	return false;
}

BulletType Player::getBulletType()
{
	return m_bulletType;
}

void Player::setBulletType(BulletType type)
{
	m_bulletType = type;
}

/// <summary>
/// Updates the player input.
/// </summary>
/// <param name="dt">The delta time</param>
void Player::Update(double dt)
{
	if (m_alive)
	{
		ProcessInput(dt);

		if (m_shieldActive)
		{
			m_timeToShieldOver -= dt;

			if (m_timeToShieldOver <= 0.0)
			{
				if (m_shieldScale <= 0.0f)
				{
					m_shieldScale = 0.0f;
					m_timeToShieldOver = MAX_SHIELD_TIME;
					m_shieldActive = false;
					m_shieldDeactive = false;
					m_playerShieldSprite.setScale(m_shieldScale, m_shieldScale);
				}
				else
				{
					m_shieldScale -= 0.001f * dt;
					m_playerShieldSprite.setScale(m_shieldScale, m_shieldScale);
				}
			}
			else
			{
				if (m_shieldScale >= 0.5f)
				{
					m_shieldScale = 0.5f;
					m_playerShieldSprite.setScale(m_shieldScale, m_shieldScale);
				}
				else
				{
					m_shieldScale += 0.001f * dt;
					m_playerShieldSprite.setScale(m_shieldScale, m_shieldScale);
				}
			}
		}
		else if (m_doubleBulletActive)
		{
			m_timeToDoubleBulletOver -= dt;

			if (m_timeToDoubleBulletOver <= 0.0)
			{
				m_timeToDoubleBulletOver = MAX_BULLET_TIME;
				m_doubleBulletActive = false;
				setBulletType(BulletType::SINGLE_BULLET);
			}
		}

		m_inSection = { (int)m_position.x / 160, (int)m_position.y / 90 };
	}
}

/// <summary>
/// Renders the player sprite with it's appropiate position and rotation transforms.
/// </summary>
/// <param name="renderTexture"></param>
void Player::Draw(sf::RenderTexture &renderTexture)
{
	m_sprite.setPosition(m_position);
	m_sprite.setRotation(m_targetOrientation);
	renderTexture.draw(m_sprite);
	if (m_shieldActive)
	{
		m_playerShieldSprite.setPosition(m_position);
		renderTexture.draw(m_playerShieldSprite);
	}
}

sf::Vector2f* Player::getPosition()
{
	return &m_position;
}

void Player::OutOfBounds()
{
	if (m_position.x < 90)
	{
		m_velocity.x *= -1;
		m_position.x += 10;
	}
	else if (m_position.x > 1830)
	{
		m_velocity.x *= -1;
		m_position.x -= 10;
	}
	
	if (m_position.y < 90)
	{
		m_velocity.y *= -1;
		m_position.y += 10;
	}
	else if (m_position.y > 1000)
	{
		m_velocity.y *= -1;
		m_position.y -= 10;
	}
}
