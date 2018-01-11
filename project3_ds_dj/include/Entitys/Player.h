#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include <iostream>
#include "XboxController.h"
#include "MathHelper.h"

enum class BulletType
{
	NORMAL,
	DOUBLE_BULLET,
	MISSILE_HOMING
};

/// <summary>
/// Player handles all update, input and rendering.
/// </summary>
class Player : public Entity
{
public:
	Player(XboxController &controller);

	void ProcessInput(double dt);
	bool FireBullet();
	BulletType getBulletType();

	virtual void Update(double dt) override;
	virtual void Draw(sf::RenderTexture &renderTexture) override;

    sf::Vector2f* getPosition();

private:
	XboxController &m_xboxController;
	float m_rotationDiff;
	const float INPUT_THRESHOLD = 30.0f;
	const uint16_t FIRE_RATE = 200;
	sf::Clock m_clock;
	float m_timeToNextShot;
	BulletType m_bulletType = BulletType::DOUBLE_BULLET;
};

#endif