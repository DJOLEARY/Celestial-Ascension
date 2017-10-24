#include "Player.h"

/// <summary>
/// 
/// </summary>
Player::Player(XboxController &controller)
	: m_xboxController(controller), m_speed(0.025f), m_rotationDiff(0.0f)
{
	if (!m_texture.loadFromFile("Assets/PlayerShip.png"))
		std::cout << "ERROR::Player::Image not loaded";

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
/// Handles the controller input for teh player mechanics in game.
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
}

/// <summary>
/// Updates the player input.
/// </summary>
/// <param name="dt">The delta time</param>
void Player::Update(double dt)
{
	ProcessInput(dt);
}

/// <summary>
/// Renders the player sprite with it's appropiate position and rotation transforms.
/// </summary>
/// <param name="renderWindow"></param>
void Player::Draw(sf::RenderWindow &renderWindow)
{
	m_sprite.setPosition(m_position);
	m_sprite.setRotation(m_targetOrientation);
	renderWindow.draw(m_sprite);
}

sf::Vector2f* Player::getPos()
{
    return &m_position;
}
