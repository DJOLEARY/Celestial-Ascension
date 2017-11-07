#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include <iostream>
#include "XboxController.h"
#include "MathHelper.h"
#include "Entitys\Bullet.h"

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
	virtual void Draw(sf::RenderTexture &renderTexture) override;

    sf::Vector2f* getPosition();

private:
	void checkBullets();

	XboxController &m_xboxController;
	// @todo(darren): May move speed into entity
	float m_rotationDiff;
	const float INPUT_THRESHOLD = 30.0f;

	std::vector<Bullet*> m_bullets;
	int m_numOfAliveBullets;
	const int MAX_BULLETS = 1;
};

#endif