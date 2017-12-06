#ifndef SHIELD_POWER_H
#define SHIELD_POWER_H

#include "Entitys\Entity.h"
#include <iostream>

class ShieldPower : public Entity
{
public:
	ShieldPower();

	void Update(double dt) override;
	void Draw(sf::RenderTexture &renderTexture) override;

private:
	sf::Sprite m_shieldProtectorSprite;
	sf::Texture m_shieldProtectorTexture;
};

#endif