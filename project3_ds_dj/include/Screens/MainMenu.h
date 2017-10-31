/// <summary>
/// @author Darren Sweeney
/// </summary>

#ifndef MAIN_MENU_SCREEN_H
#define MAIN_MENU_SCREEN_H

#include "GUI\Button.h"
#include "GUI\Label.h"
#include "GUI\Slider.h"
#include "GUI\CheckBox.h"
#include "Screen.h"

class MainMenu : public Screen
{
public:
	MainMenu();
	void update(XboxController& controller) override;
	void render(sf::RenderWindow & window) override;
	void reset() override;

private:
	void playButtonSelected();
	void optionsButtonSelected();
	void quitButtonSelected();
	void creditsButtonSelected();

	// GUI elements
	Button *m_playButton;
	Button *m_optionsButton;
	Button *m_creditsButton;
	Button *m_exitButton;

	// @todo(darren): Replace with resource manager and texture atlas
	sf::Texture m_playTexture, m_optionsTexture, m_creditsTexture, m_exitTexture;
	sf::Texture m_gameLogoTexture;
	sf::Sprite m_gameLogoSprite;

	// Rectangle and variables used for screen fading
	sf::RectangleShape m_fadeRectangle;
	float m_alphaFadeValue;
	const float FADE_RATE = 1.5f;

	// Linked to Callbacks
	bool playButtonPressed;
	bool optionsButtonPressed;
	bool exitButtonPressed;
	bool creditsButtonsPressed;

	// Used in the transition of the screen
	bool transitionIn;
	float interpolation;
};

#endif
