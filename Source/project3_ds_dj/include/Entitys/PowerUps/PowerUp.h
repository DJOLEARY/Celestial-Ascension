#ifndef POWER_UP_H
#define POWER_UP_H

#include "Entitys\Entity.h"
#include <iostream>

class PowerUp : public Entity
{
public:
	PowerUp();

	enum PowerUpType
	{
		SHIELD_POWER,
		HEART_POWER,
		DOUBLE_BULLET_POWER
	};
	PowerUpType m_type;

	void Update(double dt) override;
	void Draw(sf::RenderTexture &renderTexture) override;
	void SetPosition(sf::Vector2f &position);

	sf::Sprite m_protectorSprite;
	sf::Texture m_protectorTexture;
};

#endif