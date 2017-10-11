#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include <iostream>
#include "XboxController.h"

/// <summary>
/// Player handles all update, input and rendering.
/// </summary>
class Player : public Entity
{
public:
	Player();
	~Player();

	void ProcessInput();

	virtual void Update(double dt) override;
	virtual void Draw(sf::RenderWindow &renderWindow) override;

private:
	XboxController xboxController;
};

#endif