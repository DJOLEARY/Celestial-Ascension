/// <summary>
/// @author DJ O'Leary and Darren Sweeney
/// </summary>

#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"
#include "MathHelper.h"
#include <iostream>

enum EnemyType
{
	Wanderer,
	Turret,
	Seeker,
	Snake
};

class Enemy : public Entity
{
public:
    Enemy(sf::Vector2f *playerPos, int randNum, sf::Sound *turretShotSound);
    ~Enemy();

    virtual void Update(double dt) override;
    virtual void Draw(sf::RenderTexture &renderTexture) override;
	uint16_t getScore();
	void FireBullet();
private:

	uint16_t m_scoreValue;
    void seekPlayer();
    sf::Vector2f *m_playerPos;
	EnemyType m_enemyType;

	const uint16_t FIRE_RATE = 600;
	sf::Clock m_clock;
	float m_timeToNextShot;
	sf::Sound *m_turretShotSound;
};
#endif // !ENEMY_H