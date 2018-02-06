#ifndef DOUBLE_BULLET_POWER_H
#define DOUBLE_BULLET_POWER_H

#include "Entitys\PowerUps\PowerUp.h"
#include <iostream>

class DoubleBulletPowerUp : public PowerUp
{
public:
	DoubleBulletPowerUp(sf::Vector2f &position);
};

#endif