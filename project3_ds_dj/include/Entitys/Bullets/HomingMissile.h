#ifndef HOMING_MISSILE
#define HOMING_MISSILE

#include "Entitys\Bullets\Bullet.h"

class HomingMissile : public Bullet
{
	HomingMissile(const sf::Vector2f &position, const sf::Vector2f &direction);

	void Update(double dt) override;
};

#endif // !HOMING_MISSILE