#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include <iostream>
#include "XboxController.h"
#include "MathHelper.h"
#include "Entitys\Bullet.h"
#include "CircularArray.h"

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
	// Player
	XboxController &m_xboxController;
	float m_rotationDiff;
	const float INPUT_THRESHOLD = 30.0f;

	//	Bullet
	void bulletUpdate(double dt);
	void bulletDraw(sf::RenderTexture & renderTexture);
	void fire(sf::Vector2f playerPos, sf::Vector2f rightStick);
	typedef CircularArray<Bullet> BulletArray;
	BulletArray m_bulletArray;
};

#endif