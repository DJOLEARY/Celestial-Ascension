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
	void setScore(uint16_t score);
	uint32_t *getScore();
	void setWave(uint8_t wave);
	void setLives(uint8_t lives);

private:
	sf::Texture m_leftHUDTex, m_rightHUDTex;
	sf::Sprite m_leftHUDSprite, m_rightHUDSprite;
	sf::Texture m_heartTexture;
	sf::Sprite m_heartSprite;
	sf::Font m_font;
	sf::Text m_scoreText, m_waveNumText;
	uint32_t m_currentScore;
	// Want to have the score increment on screen, nice visual effect
	uint32_t m_displayScore;
	bool displayNewWave;
	uint8_t m_lives;
	static const int MAX_LIVES = 5;
	sf::Vector2f m_heartPositions[MAX_LIVES];
	sf::Clock m_clock;
	uint16_t m_timeToWaveUILerp;
	sf::Text m_waveText;
	sf::Vector2f m_waveTextOffset;
	sf::Vector2f m_targetWaveNumPos;
};

#endif