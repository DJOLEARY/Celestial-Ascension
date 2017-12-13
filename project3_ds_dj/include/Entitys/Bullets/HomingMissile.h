#ifndef HOMING_MISSILE
#define HOMING_MISSILE

#include "Entitys\Bullets\Bullet.h"

class HomingMissile : public Bullet
{
public:
	HomingMissile(const sf::Vector2f &position, const sf::Vector2f &direction);
	void Update(double dt) override;
	void setEnemyPosition(sf::Vector2f &pos);

private:
	sf::Vector2f m_enemyPosition;
	float m_rotation, m_targetRotation;
	const float TURN_RATE = 10.0f;
};

#endif // !HOMING_MISSILE