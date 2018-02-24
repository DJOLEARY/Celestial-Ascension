#ifndef SHIELD_POWER_H
#define SHIELD_POWER_H

#include "Entitys\PowerUps\PowerUp.h"
#include <iostream>

class ShieldPower : public PowerUp
{
public:
	ShieldPower(sf::Vector2f &position);
};

#endif