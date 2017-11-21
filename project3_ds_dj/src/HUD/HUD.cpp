#include "..\HUD\HUD.h"

HUD::HUD()
{
	if (!m_leftHUDTex.loadFromFile("Assets/HUD/left_HUD.png"))
		std::cout << "HUD::left hud texture is not laoded" << std::endl;

	if (!m_rightHUDTex.loadFromFile("Assets/HUD/right_HUD.png"))
		std::cout << "HUD::left hud texture is not laoded" << std::endl;

	if (!m_font.loadFromFile("Assets/Fonts/OCRAEXT.TTF"))
		std::cout << "HUD::font has not loaded" << std::endl;

	m_leftHUDSprite.setTexture(m_leftHUDTex);
	m_leftHUDSprite.setScale(sf::Vector2f(0.5f, 0.5f));
	m_rightHUDSprite.setTexture(m_rightHUDTex);
	m_rightHUDSprite.setScale(sf::Vector2f(0.5f, 0.5f));
	m_scoreText.setFont(m_font);
	m_scoreText.setFillColor(sf::Color(226.0f, 96.0f, 9.0f));
	m_scoreText.setString("213672");
	m_waveNumText.setFont(m_font);
	m_waveNumText.setFillColor(sf::Color(226.0f, 96.0f, 9.0f));
	m_waveNumText.setString("42");
	m_waveNumText.setCharacterSize(50);
}

void HUD::setScore(uint16_t score)
{
	m_scoreText.setString(std::to_string(score));
}

void HUD::setWave(uint8_t wave)
{	
	m_waveNumText.setString(std::to_string(wave));
}

void HUD::update(sf::Int32 dt, sf::Vector2f &pos)
{
	m_leftHUDSprite.setPosition(pos + sf::Vector2f(-930.0f, -510.0f));
	m_rightHUDSprite.setPosition(pos + sf::Vector2f(760.0f, -510.0f));
	m_scoreText.setPosition(pos + sf::Vector2f(-700.0f, -445.0f));
	m_waveNumText.setPosition(pos + sf::Vector2f(815.0f, -465.0f));
}

void HUD::render(sf::RenderTexture &texture)
{
	texture.draw(m_leftHUDSprite);
	texture.draw(m_rightHUDSprite);
	texture.draw(m_scoreText);
	texture.draw(m_waveNumText);
}