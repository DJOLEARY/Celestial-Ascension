#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"

class Player : public Entity
{
public:
	Player();
	~Player();

	virtual void Update(double dt) override;
	virtual void Draw(sf::RenderWindow &renderWindow) override;
};

#endif