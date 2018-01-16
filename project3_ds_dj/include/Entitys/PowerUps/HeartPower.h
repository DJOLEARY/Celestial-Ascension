#ifndef HEART_POWER_H
#define HEART_POWER_H

#include "Entitys\PowerUps\PowerUp.h"
#include <iostream>

class HeartPower : public PowerUp
{
public:
	HeartPower(sf::Vector2f &position);
};

#endif