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
	Bullet(sf::Vector2f playerPos, XboxController& controller);
	~Bullet();

	virtual void Update(double dt) override;
	virtual void Draw(sf::RenderTexture& renderTexture) override;

private:
	float m_speed;

	void createVelocity();
};

#endif // !BULLET_H