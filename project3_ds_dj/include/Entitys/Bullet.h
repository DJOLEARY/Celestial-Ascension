/// <summary>
/// @author DJ O'Leary
/// </summary>

#ifndef BULLET_H
#define BULLET_H
#include "Entity.h"
#include "MathHelper.h"
#include "XboxController.h"

class Bullet : public Entity
{
public:
	Bullet();
	Bullet(sf::Vector2f playerPos, sf::Vector2f rightStick);
	~Bullet();

	virtual void Update(double dt) override;
	virtual void Draw(sf::RenderTexture& renderTexture) override;

	void setAttributes(sf::Vector2f playerPos, sf::Vector2f rightStick);

private:

	void createVelocity();
};

#endif // !BULLET_H