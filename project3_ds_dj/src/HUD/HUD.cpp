#include "..\HUD\HUD.h"

HUD::HUD()
	: m_lives(3)
{
	if (!m_leftHUDTex.loadFromFile("Assets/HUD/left_HUD.png"))
		std::cout << "HUD::left hud texture is not laoded" << std::endl;

	if (!m_rightHUDTex.loadFromFile("Assets/HUD/right_HUD.png"))
		std::cout << "HUD::left hud texture is not laoded" << std::endl;

	if (!m_heartTexture.loadFromFile("Assets/HUD/heart.png"))
		std::cout << "HUD::heart texture has not loaded" << std::endl;

	if (!m_font.loadFromFile("Assets/Fonts/OCRAEXT.TTF"))
		std::cout << "HUD::font has not loaded" << std::endl;

	m_leftHUDSprite.setTexture(m_leftHUDTex);
	m_leftHUDSprite.setScale(sf::Vector2f(0.5f, 0.5f));
	m_rightHUDSprite.setTexture(m_rightHUDTex);
	m_rightHUDSprite.setScale(sf::Vector2f(0.5f, 0.5f));
	m_heartSprite.setTexture(m_heartTexture);
	m_heartSprite.setScale(sf::Vector2f(0.5f, 0.5f));
	m_scoreText.setFont(m_font);
	m_scoreText.setFillColor(sf::Color(226.0f, 96.0f, 9.0f));
	m_scoreText.setString("1000");
	m_waveNumText.setFont(m_font);
	m_waveNumText.setFillColor(sf::Color(226.0f, 96.0f, 9.0f));
	m_waveNumText.setString("1");
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

void HUD::setLives(uint8_t lives)
{
	m_lives = lives;

	if (m_lives > MAX_LIVES)
	{
		m_lives = MAX_LIVES;
	}
}

void HUD::update(sf::Int32 dt, sf::Vector2f &pos)
{
	m_leftHUDSprite.setPosition(pos + sf::Vector2f(-930.0f, -510.0f));
	m_heartSprite.setPosition(pos + sf::Vector2f(-770.0f, -465.0f));
	m_rightHUDSprite.setPosition(pos + sf::Vector2f(760.0f, -510.0f));
	for (uint8_t i = 0; i < m_lives; i++)
	{
		m_heartPositions[i] = pos + sf::Vector2f(-770.0f + (i * 25.0f), -460.0f);
	}

	float scoreTextWidth = m_scoreText.getLocalBounds().width;
	m_scoreText.setPosition(pos + sf::Vector2f(-570.0f - scoreTextWidth, -440.0f));
	m_waveNumText.setPosition(pos + sf::Vector2f(830.0f, -470.0f));
}

void HUD::render(sf::RenderTexture &texture)
{
	texture.draw(m_leftHUDSprite);
	for (uint8_t i = 0; i < m_lives; i++)
	{
		m_heartSprite.setPosition(m_heartPositions[i]);
		texture.draw(m_heartSprite);
	}
	texture.draw(m_rightHUDSprite);
	texture.draw(m_scoreText);
	texture.draw(m_waveNumText);
}