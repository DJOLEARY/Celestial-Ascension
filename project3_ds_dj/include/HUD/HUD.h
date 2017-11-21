#ifndef HUD_H
#define HUD_H

#include <SFML\Graphics.hpp>
#include <iostream>

class HUD
{
public:
	HUD();
	void update(sf::Int32 dt, sf::Vector2f &pos);
	void render(sf::RenderTexture &texture);

private:
	sf::Texture m_leftHUDTex, m_rightHUDTex;
	sf::Sprite m_leftHUDSprite, m_rightHUDSprite;

};

#endif