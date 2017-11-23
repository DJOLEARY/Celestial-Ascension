#ifndef BulletManager_H
#define BulletManager_H

#include "CircularArray.h"
#include "Bullet.h"
#include "XboxController.h"

class BulletManager
{
public:
	BulletManager(sf::Rect<float> &m_worldBound, XboxController &controller);
	~BulletManager();

	void update(double dt);
	void draw(sf::RenderTexture & renderTexture);
	void createBullet();
	void clearBullets();

	void setPlayer(sf::Vector2f *playerPos);

private:

	typedef CircularArray<Bullet> BulletArray;
	BulletArray m_bulletArray;
	sf::Texture m_bulletTexture;
	sf::Sprite m_bulletSprite;
	sf::Rect<float> m_worldBound;

	sf::Vector2f *m_playerPos;
	XboxController &m_controller;

	const float INPUT_THRESHOLD = 30.0f;
};

#endif // !BulletManager_H