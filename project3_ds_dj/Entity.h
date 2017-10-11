#ifndef ENTITY_H
#define ENTITY_H

#include <SFML\Graphics.hpp>

/// <summary>
/// Base class for game entities in the game scene.
/// </summary>
class Entity
{
public:
	Entity() {};
	virtual ~Entity() {};

	virtual void Update(double dt) = 0;
	virtual void Draw(sf::RenderWindow &renderWindow) = 0;

protected:
	sf::Texture m_texture;
	sf::Image m_image;		// @note(darren): Do i need this for each texture? What about snake enemy.
	sf::Vector2f m_position;
	sf::Vector2f m_velocity;
	// @note(darren): Possible store orientation here?
};

#endif