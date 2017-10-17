#include "Player.h"

/// <summary>
/// 
/// </summary>
Player::Player()
	: m_xboxController(CONTROLLER_ONE), m_speed(0.01f)
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
		m_orientation = atan2(m_velocity.y, m_velocity.x);
		m_velocity = m_speed * m_movementDir * (float)dt;
	}
	
	m_position += m_velocity * (float)dt;

	if (sf::magnitude(m_velocity) > 0)
	{
		m_velocity *= 0.99f;
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
	m_sprite.setRotation((m_orientation * 180) / 3.14);
	renderWindow.draw(m_sprite);
}