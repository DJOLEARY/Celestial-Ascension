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
	sf::Sprite m_sprite;
	sf::Vector2f m_position;
	sf::Vector2f m_velocity;
	sf::Vector2f m_accleration;
	sf::Vector2f m_movementDir;
	float m_orientation;
};

#endif