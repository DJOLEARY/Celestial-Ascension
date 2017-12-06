#ifndef ENTITY_H
#define ENTITY_H

#include <SFML\Graphics.hpp>

enum EntityType
{
	PLAYER,
	ENEMY,
	SHIELD_POWER,
	HEART_POWER
};

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

	sf::Vector2f getPos();
	int getType();
	sf::Vector2i getSection();

protected:
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	sf::Vector2f m_position;
	float m_speed;
	sf::Vector2f m_velocity;
	sf::Vector2f m_accleration;
	sf::Vector2f m_movementDir;
	float m_orientation;
	float m_targetOrientation;
	int m_type;	// What type the current Entity is. (e.g. player, enemy).
	sf::Vector2i m_inSection;	// What section the centre of the Entity is in.
	bool m_alive;	// Whether to update/draw the current Entity.
};

#endif