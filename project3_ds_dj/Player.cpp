#include "Player.h"

Player::Player()
{
	m_texture.loadFromFile("");
}

Player::~Player()
{

}

void Player::Update(double dt)
{

}

void Player::Draw(sf::RenderWindow &renderWindow)
{
	// @note(darren): Need to look at documentation with rendering textures and loading, 
	//					commit from home pc for now.
	//renderWindow.draw(m_texture);
}