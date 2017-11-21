#include "..\HUD\HUD.h"

HUD::HUD()
{
	if (!m_leftHUDTex.loadFromFile("Assets/HUD/left_HUD.png"))
		std::cout << "HUD::left hud texture is not laoded" << std::endl;

	if (!m_rightHUDTex.loadFromFile("Assets/HUD/right_HUD.png"))
		std::cout << "HUD::left hud texture is not laoded" << std::endl;

	m_leftHUDSprite.setTexture(m_leftHUDTex);
	m_leftHUDSprite.setScale(sf::Vector2f(0.5f, 0.5f));
	m_rightHUDSprite.setTexture(m_rightHUDTex);
	m_rightHUDSprite.setScale(sf::Vector2f(0.5f, 0.5f));
}

void HUD::update(sf::Int32 dt, sf::Vector2f &pos)
{
	m_leftHUDSprite.setPosition(pos + sf::Vector2f(-930.0f, -510.0f));
	m_rightHUDSprite.setPosition(pos + sf::Vector2f(760.0f, -510.0f));
}

void HUD::render(sf::RenderTexture &texture)
{
	texture.draw(m_leftHUDSprite);
	texture.draw(m_rightHUDSprite);
}