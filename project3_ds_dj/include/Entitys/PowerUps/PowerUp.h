#ifndef POWER_UP_H
#define POWER_UP_H

#include "Entitys\Entity.h"
#include <iostream>

class PowerUp : public Entity
{
public:
	PowerUp();

	void Update(double dt) override;
	void Draw(sf::RenderTexture &renderTexture) override;

private:
	sf::Sprite m_protectorSprite;
	sf::Texture m_protectorTexture;
};

#endif