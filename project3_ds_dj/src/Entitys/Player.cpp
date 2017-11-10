#include "Entitys\Player.h"

/// <summary>
/// 
/// </summary>
Player::Player(XboxController &controller)
	: m_xboxController(controller), m_rotationDiff(0.0f)
{
	if (!m_texture.loadFromFile("Assets/PlayerShip.png"))
	{
		std::cout << "ERROR::Player::Image not loaded";
	}

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
		//m_targetOrientation += 180.0f;	// Put into 0 - 360 range
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

	/*if (sf::magnitude(m_xboxController.getRightStick()) > INPUT_THRESHOLD && m_numOfAliveBullets < MAX_BULLETS)
	{
		m_bullets.push_back(new Bullet(m_position, rightStick));
		m_numOfAliveBullets++;
	}*/
}

/// <summary>
/// Updates the player input.
/// </summary>
/// <param name="dt">The delta time</param>
void Player::Update(double dt)
{
	ProcessInput(dt);
	/*checkBullets();

	for (Bullet* bullet : m_bullets)
	{
		bullet->Update(dt);
	}*/
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

	for (Bullet* bullet : m_bullets)
	{
		bullet->Draw(renderTexture);
	}
}

sf::Vector2f* Player::getPosition()
{
	return &m_position;
}

void Player::checkBullets()
{
	int index = 0;
	for (Bullet* bullet : m_bullets)
	{
		if (bullet->getPos().x < 0 || bullet->getPos().x > 1920 || bullet->getPos().y < 0 || bullet->getPos().y > 1080)
		{
			deleteBullet(index);
		}
		else
		{
			index++;
		}
	}
}

void Player::deleteBullet(int index)
{
	m_bullets.erase(m_bullets.begin() + index);
	m_numOfAliveBullets--;
}