#ifndef SPLASH_SCREEN_H
#define SPLASH_SCREEN_H

#include "Screen.h"

class SplashScreen : public Screen
{
public:
	SplashScreen();
	void update(XboxController &controller) override;
	void render(sf::RenderTexture & renderTexture) override;

private:
	sf::Texture m_teamLogoTexture;
	sf::Sprite m_teamLogoSprite;

	sf::Clock m_timeTillFade;
	sf::RectangleShape m_fadeRectangle;
	float m_alphaFadeValue;
	const float FADE_RATE = 3.5f;
};

#endif