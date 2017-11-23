#include "Entitys\Player.h"

/// <summary>
/// 
/// </summary>
Player::Player(XboxController &controller) : 
	m_xboxController(controller), m_rotationDiff(0.0f),
	m_bulletArray(100)
{
	if (!m_texture.loadFromFile("Assets/PlayerShip.png"))
	{
		std::cout << "ERROR::Player::Image not loaded";
	}

	m_type = EntityType::PLAYER;
	m_alive = true;

	m_speed = 0.025f;
	m_sprite.setTexture(m_texture);
	m_sprite.setScale(sf::Vector2f(0.3f, 0.3f));
	m_sprite.setOrigin(m_sprite.getLocalBounds().width / 2.0f, m_sprite.getLocalBounds().height / 2.0f);
}

/// <summary>
/// 
/// </summary>
Player::~Player()
{

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

	sf::Vector2f rightStick = m_xboxController.getRightStick();

	if (sf::magnitude(rightStick) > INPUT_THRESHOLD)
	{
		fire(m_position, rightStick);
	}
}

/// <summary>
/// Updates the player input.
/// </summary>
/// <param name="dt">The delta time</param>
void Player::Update(double dt)
{
	bulletUpdate(dt);
	ProcessInput(dt);

	m_inSection = { (int)m_position.x / 160, (int)m_position.y / 90 };
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

	bulletDraw(renderTexture);
}

sf::Vector2f* Player::getPosition()
{
	return &m_position;
}

void Player::bulletUpdate(double dt)
{
	uint16_t removalCount = 0;

	for (uint16_t bulletIndex = 0; bulletIndex < m_bulletArray.getCount(); bulletIndex++)
	{
		Bullet &bullet = m_bulletArray[bulletIndex];
		m_bulletArray.swap(bulletIndex - removalCount, bulletIndex);
		bullet.Update(dt);

		if (bullet.getAlive() == false)
		{
			removalCount++;
		}
	}

	m_bulletArray.setCount(m_bulletArray.getCount() - removalCount);
}

void Player::bulletDraw(sf::RenderTexture & renderTexture)
{
	for (uint16_t bulletIndex = 0; bulletIndex < m_bulletArray.getCount(); bulletIndex++)
	{
		m_bulletArray[bulletIndex].Draw(renderTexture);
	}
}

void Player::fire(sf::Vector2f playerPos, sf::Vector2f rightStick)
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
	if (m_bulletArray.getCount() > 25)
	{
		std::cout << std::endl;
	}

	Bullet &bullet = m_bulletArray[index];
	bullet.setAttributes(playerPos, rightStick);
}