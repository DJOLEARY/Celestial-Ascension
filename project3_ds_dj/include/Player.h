#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include <iostream>
#include "XboxController.h"
#include "MathHelper.h"

/// <summary>
/// Player handles all update, input and rendering.
/// </summary>
class Player : public Entity
{
public:
	Player(XboxController &controller);
	~Player();

	void ProcessInput(double dt);

	virtual void Update(double dt) override;
	virtual void Draw(sf::RenderWindow &renderWindow) override;

    sf::Vector2f* getPos();
	sf::Vector2f getVelocity();

private:
	XboxController &m_xboxController;
	// @todo(darren): May move speed into entity
	float m_speed;
	float m_rotationDiff;
	const float INPUT_THRESHOLD = 30.0f;
};

#endif