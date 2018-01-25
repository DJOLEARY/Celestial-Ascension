#include "Screens\SplashScreen.h"

SplashScreen::SplashScreen(sf::View &view)
	: Screen(GameState::SplashScreen, view), m_alphaFadeValue(0)
{
	if(!m_teamLogoTexture.loadFromFile("Assets/SplashScreen/dragon.png"))
		std::cout << "ERROR::SplashScreen::Team Logo image not loaded";

	m_teamLogoSprite.setTexture(m_teamLogoTexture);
	m_teamLogoSprite.setPosition(sf::Vector2f(1920.0f / 2, 1080.0f / 2));
	m_teamLogoSprite.setOrigin(m_teamLogoSprite.getLocalBounds().width / 2.0f, m_teamLogoSprite.getLocalBounds().height / 2.0f);
	m_teamLogoSprite.setColor(sf::Color(255, 0, 191));

	m_fadeRectangle.setFillColor(sf::Color(0, 0, 0, m_alphaFadeValue));
	m_fadeRectangle.setSize(sf::Vector2f(1920.0f, 1080.0f));
}

void SplashScreen::update(XboxController &controller, sf::Int32 dt)
{
	if (controller.isButtonPressed(XBOX360_A)
		|| controller.isButtonPressed(XBOX360_START))
	{
		m_nextGameState = GameState::MainMenu;
	}

	if (m_timeTillFade.getElapsedTime().asSeconds() > 2)
	{
		m_alphaFadeValue += FADE_RATE;

		if (m_alphaFadeValue > 220)
			m_nextGameState = GameState::MainMenu;

		m_fadeRectangle.setFillColor(sf::Color(0, 0, 0, m_alphaFadeValue));
	}
}

void SplashScreen::render(sf::RenderTexture &renderTexture)
{
	renderTexture.setView(m_view);
	renderTexture.clear(sf::Color(0, 0, 0));
	renderTexture.draw(m_teamLogoSprite);
	renderTexture.draw(m_fadeRectangle);
}