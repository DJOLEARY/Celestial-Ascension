#ifndef ENTITY_H
#define ENTITY_H

#include <SFML\Graphics.hpp>

/// <summary>
/// Base class for game entities in the game scene.
/// </summary>
class Entity
{
public:
	Entity() : m_orientation(0.0f), m_targetOrientation(0.0f), m_alive(true) {};
	virtual ~Entity() {};

	virtual void Update(double dt) = 0;
	virtual void Draw(sf::RenderTexture &renderTexture) = 0;

	sf::Vector2f getPos();
	sf::Vector2i getSection();
	sf::Sprite getSprite();

	bool getAlive();
	void setAlive(bool isAlive);

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
	sf::Vector2i m_inSection;	// What section the centre of the Entity is in.
	bool m_alive;	// Whether to update/draw the current Entity.
};

#endif