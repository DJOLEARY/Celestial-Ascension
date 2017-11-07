#ifndef ENTITY_H
#define ENTITY_H

#include <SFML\Graphics.hpp>

/// <summary>
/// Base class for game entities in the game scene.
/// </summary>
class Entity
{
public:
	Entity() : m_orientation(0.0f), m_targetOrientation(0.0f) {};
	virtual ~Entity() {};

	virtual void Update(double dt) = 0;
	virtual void Draw(sf::RenderTexture &renderTexture) = 0;

	std::string getType();
	sf::Vector2f getPos();

protected:
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	sf::Vector2f m_position;
	sf::Vector2f m_velocity;
	sf::Vector2f m_accleration;
	sf::Vector2f m_movementDir;
	float m_orientation;
	float m_targetOrientation;
	std::string m_type;
};

#endif