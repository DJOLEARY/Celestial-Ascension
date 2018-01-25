#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h" 
#include <iostream>
#include "XboxController.h"
#include "MathHelper.h"

enum class BulletType
{
	SINGLE_BULLET,
	DOUBLE_BULLET,
	MISSILE_HOMING
};

/// <summary>
/// Player handles all update, input and rendering.
/// </summary>
class Player : public Entity
{
public:
	Player(XboxController &controller, sf::Sound *shotSound);

	void ProcessInput(double dt);
	bool FireBullet();
	BulletType getBulletType();
	uint32_t m_lives;
	bool m_shieldActive;

	virtual void Update(double dt) override;
	virtual void Draw(sf::RenderTexture &renderTexture) override;

    sf::Vector2f* getPosition();
	void OutOfBounds();

private:
	void SpawnPlayer();

	XboxController &m_xboxController;
	float m_rotationDiff;
	const float INPUT_THRESHOLD = 30.0f;
	const uint16_t FIRE_RATE = 200;
	const uint8_t TIME_TO_SPAWN = 2;
	sf::Clock m_clock;
	float m_timeToNextShot;
	BulletType m_bulletType = BulletType::SINGLE_BULLET;
	const double MAX_SHIELD_TIME = 6000.0;
	float m_shieldScale;
	bool m_shieldDeactive;
	double m_timeToShieldOver;
	sf::Sprite m_playerShieldSprite;
	sf::Texture m_playerShieldTexture;
	sf::Sound* m_shotSound;
};

#endif