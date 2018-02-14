#include "..\HUD\HUD.h"
#include "MathHelper.h"

HUD::HUD()
	: m_lives(3), m_timeToWaveUILerp(0), m_displayScore(0)
{
	if (!m_leftHUDTex.loadFromFile("Assets/HUD/left_HUD.png"))
		std::cout << "HUD::left hud texture is not laoded" << std::endl;

	if (!m_rightHUDTex.loadFromFile("Assets/HUD/right_HUD.png"))
		std::cout << "HUD::left hud texture is not laoded" << std::endl;

	if (!m_heartTexture.loadFromFile("Assets/HUD/heart_2.png"))
		std::cout << "HUD::heart texture has not loaded" << std::endl;

	if (!m_font.loadFromFile("Assets/Fonts/OCRAEXT.TTF"))
		std::cout << "HUD::font has not loaded" << std::endl;

	m_leftHUDSprite.setTexture(m_leftHUDTex);
	m_leftHUDSprite.setScale(sf::Vector2f(0.5f, 0.5f));
	m_rightHUDSprite.setTexture(m_rightHUDTex);
	m_rightHUDSprite.setScale(sf::Vector2f(0.5f, 0.5f));
	m_heartSprite.setTexture(m_heartTexture);
	m_heartSprite.setColor(sf::Color(183, 27, 121));
	m_scoreText.setFont(m_font);
	m_scoreText.setFillColor(sf::Color(226.0f, 96.0f, 9.0f));
	m_scoreText.setString("1000");
	m_waveNumText.setFont(m_font);
	m_waveNumText.setFillColor(sf::Color(226.0f, 96.0f, 9.0f));
	m_waveNumText.setString("1");
	m_waveNumText.setCharacterSize(80);
	m_targetWaveNumPos = sf::Vector2f(815.0f, -470.0f);

	m_waveText.setFont(m_font);
	m_waveText.setFillColor(sf::Color(226.0f, 96.0f, 9.0f));
	m_waveText.setString("Wave");
	m_waveText.setCharacterSize(80);
	m_waveTextOffset = sf::Vector2f(160.0f, 150.0f);

	m_multiplierText.setFont(m_font);
	m_multiplierText.setFillColor(sf::Color(226.0f, 96.0f, 9.0f));
	m_multiplierText.setCharacterSize(40);
}

void HUD::setScore(uint16_t score)
{
	m_scoreText.setString(std::to_string(score));

	if (score == 0)
	{
		m_displayScore = 0;
		m_currentScore = 0;
	}
}

uint32_t *HUD::getScore()
{
	return &m_currentScore;
}

void HUD::setWave(uint8_t wave)
{	
	if(wave < 10)
		m_waveNumText.setString("0" + std::to_string(wave));
	else
		m_waveNumText.setString(std::to_string(wave));

	displayNewWave = true;
	m_timeToWaveUILerp = 0;
	m_waveNumText.setCharacterSize(80);
}

void HUD::setLives(uint8_t lives)
{
	m_lives = lives;

	if (m_lives > MAX_LIVES)
	{
		m_lives = MAX_LIVES;
	}
}

void HUD::setMultiplier(int multiplier)
{
	m_multiplier = multiplier;
	
	if (m_multiplier < 10)
	{
		m_multiplierText.setString("x0" + std::to_string(m_multiplier));
	}
	else
	{
		m_multiplierText.setString("x" + std::to_string(m_multiplier));
	}
}

void HUD::update(sf::Int32 dt, sf::Vector2f &pos)
{
	if (m_displayScore < m_currentScore)
	{
		if (m_currentScore - m_displayScore < 10)
		{
			m_displayScore += 1;
		}
		else if (m_currentScore - m_displayScore < 100)
		{
			m_displayScore += 5;
		}
		else if (m_currentScore - m_displayScore < 1000)
		{
			m_displayScore += 50;
		}
		else
		{
			m_displayScore += 500;
		}
	}

	m_leftHUDSprite.setPosition(pos + sf::Vector2f(-930.0f, -510.0f));
	m_heartSprite.setPosition(pos + sf::Vector2f(-770.0f, -465.0f));
	m_rightHUDSprite.setPosition(pos + sf::Vector2f(760.0f, -510.0f));
	for (uint8_t i = 0; i < m_lives; i++)
	{
		m_heartPositions[i] = pos + sf::Vector2f(-770.0f + (i * 35.0f), -460.0f);
	}

	m_multiplierText.setPosition(pos + sf::Vector2f(-880.0f, -452.5f));

	float scoreTextWidth = m_scoreText.getLocalBounds().width;
	m_scoreText.setPosition(pos + sf::Vector2f(-570.0f - scoreTextWidth, -438.0f));

	sf::Time elapsedTime = m_clock.getElapsedTime();
	if (displayNewWave)
	{
		if (m_timeToWaveUILerp <= 2)
		{
			m_waveNumText.setPosition(pos - sf::Vector2f(-60.0f, 150.0f));
			m_waveText.setPosition(pos - m_waveTextOffset);

			if (elapsedTime.asSeconds() > 1)
			{
				m_timeToWaveUILerp++;
				m_clock.restart();
			}
		}
		else
		{
			sf::Vector2f lerpWaveNumPos = sf::lerp(pos - sf::Vector2f(-30.0f, 150.0f), 
				pos + m_targetWaveNumPos, elapsedTime.asSeconds() * 2);
			float interpolate = elapsedTime.asSeconds() * 2;
			if (interpolate >= 1.0f)
				interpolate = 1.0f;
			int lerpFontSize = sf::floatLerp(80, 50, interpolate);
			m_waveNumText.setCharacterSize(lerpFontSize);
			m_waveNumText.setPosition(lerpWaveNumPos);

			sf::Vector2f lerpWaveTextPos = sf::lerp(pos - m_waveTextOffset, 
				pos - m_waveTextOffset - sf::Vector2f(1000.0f, 0.0f), elapsedTime.asSeconds() * 2);
			m_waveText.setPosition(lerpWaveTextPos);

			if (elapsedTime.asSeconds() > 0.5)
			{
				displayNewWave = false;
				m_clock.restart();
			}
		}
	}
	else
	{
		m_waveNumText.setPosition(pos + m_targetWaveNumPos);
	}
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
	m_scoreText.setString(std::to_string(m_displayScore));
	texture.draw(m_scoreText);
	texture.draw(m_waveNumText);
	if(displayNewWave)
		texture.draw(m_waveText);
	texture.draw(m_multiplierText);
}