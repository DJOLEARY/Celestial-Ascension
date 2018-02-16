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
	MainMenu(sf::View &view, sf::Sound *confirmSound, sf::Sound *navigateSound);
	void update(XboxController& controller, sf::Int32 dt) override;
	void render(sf::RenderTexture & renderTexture) override;
	void reset() override;

private:
	void playButtonSelected();
	void optionsButtonSelected();
	void quitButtonSelected();
	void creditsButtonSelected();

	// GUI elements
	Button *m_logo;
	Button *m_playButton;
	Button *m_optionsButton;
	Button *m_creditsButton;
	Button *m_exitButton;

	// @todo(darren): Replace with resource manager and texture atlas
	sf::Texture m_playTexture, m_optionsTexture, m_creditsTexture, m_exitTexture;
	sf::Texture m_gameLogoTexture;

	// Rectangle and variables used for screen fading
	sf::RectangleShape m_fadeRectangle;
	float m_alphaFadeValue;
	const float FADE_RATE = 3.5f;

	// Linked to Callbacks
	bool playButtonPressed;
	bool optionsButtonPressed;
	bool exitButtonPressed;
	bool creditsButtonsPressed;

	// Used in the transition of the screen
	bool transitionIn;
	float interpolation;

	sf::Sound *m_confirmSound;
	sf::Sound *m_navigateSound;
};

#endif
