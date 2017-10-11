#include "Player.h"

/// <summary>
/// 
/// </summary>
Player::Player()
	: xboxController(CONTROLLER_ONE)
{
	if (!m_texture.loadFromFile("Assets/PlayerShip.png"))
		std::cout << "ERROR::Player::Image not loaded";

	m_sprite.setTexture(m_texture);
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
void Player::ProcessInput()
{
	if (xboxController.isButtonPressed(XBOX360_A))
	{
		std::cout << "Button A pressed" << std::endl;
	}

	if (xboxController.getLeftStick().x > 10.0f)
		m_position.x += 0.1f;

	if (xboxController.getLeftStick().x < -10.0f)
		m_position.x -= 0.1f;

	if (xboxController.getLeftStick().y > 10.0f)
		m_position.y += 0.1f;

	if (xboxController.getLeftStick().y < -10.0f)
		m_position.y -= 0.1f;
}

/// <summary>
/// Updates the player input.
/// </summary>
/// <param name="dt">The delta time</param>
void Player::Update(double dt)
{
	ProcessInput();
}

/// <summary>
/// Renders the player sprite with it's appropiate position and rotation transforms.
/// </summary>
/// <param name="renderWindow"></param>
void Player::Draw(sf::RenderWindow &renderWindow)
{
	m_sprite.setPosition(m_position);
	renderWindow.draw(m_sprite);
}