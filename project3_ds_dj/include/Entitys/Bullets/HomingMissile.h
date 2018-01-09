#ifndef HOMING_MISSILE
#define HOMING_MISSILE

#include "Entitys\Bullets\Bullet.h"

class HomingMissile : public Bullet
{
public:
	HomingMissile(const sf::Vector2f &position, const sf::Vector2f &direction, sf::Vector2f *enemyPos);
	void Update(double dt) override;

private:
	sf::Vector2f &m_enemyPosition;
	float m_rotation, m_targetRotation;
	float m_rotationDiff;
	const float TURN_RATE = 0.001f;
};

#endif // !HOMING_MISSILE