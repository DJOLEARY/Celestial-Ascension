/// <summary>
/// @author Darren Sweeney
/// </summary>

#ifndef MAIN_MENU_SCREEN_H
#define MAIN_MENU_SCREEN_H

#include "GUI\Button.h"
#include "GUI\Label.h"
#include "GUI\Slider.h"
#include "GUI\CheckBox.h"
#include "GUI\RadioButtons.h"
#include "Screen.h"

class MainMenu: public Screen
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
	Label *m_gameTitle;
	Button *m_playButton;
	Button *m_optionsButton;
	Button *m_creditsButton;
	Button *m_quitButton;

	sf::Texture buttonOneTexture, buttonTwoTexture;

	// Rectangle and variables used for screen fading
	sf::RectangleShape m_fadeRectangle;
	float m_alphaFadeValue;
	const float FADE_RATE = 1.5f;

	// Linked to Callbacks
	bool playButtonPressed;
	bool optionsButtonPressed;
	bool quitButtonPressed;
	bool creditsButtonsPress;

	// Used in the transition of the screen
	bool transitionIn;
	float interpolation;
};

#endif
