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
	Player();
	~Player();

	void ProcessInput(double dt);

	virtual void Update(double dt) override;
	virtual void Draw(sf::RenderWindow &renderWindow) override;

private:
	XboxController m_xboxController;
	// @todo(darren): May move speed into entity
	float m_speed;
	const float INPUT_THRESHOLD = 50.0f;
};

#endif