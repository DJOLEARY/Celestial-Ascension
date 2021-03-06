/// <summary>
/// @author Darren Sweeney
/// </summary>

#ifndef EXIT_MENU_H
#define EXIT_MENU_H

#include <SFML\Graphics.hpp>
#include "XboxController.h"
#include "GUI\Button.h"
#include "GUI\Label.h"
#include "Screen.h"

class ExitMenu : public Screen
{
public:
	ExitMenu(sf::View &view, sf::Sound *confirmSound, sf::Sound *navigateSound, sf::Sound *backSound);
	void update(XboxController& controller, sf::Int32 dt) override;
	void reset() override;
	bool getExitState();

private:
	void yesButtonSelected();
	void noButtonSelected();

	// GUI elements
	Label *m_exitGameLabel;
	Label *m_areYouSureLabel;
	Button *m_yesButton, *m_noButton;
	sf::Texture m_yesTexture, m_noTexture;

	bool m_noButtonPressed, m_yesButtonPressed;
	bool transitionIn;
	float interpolation;
	sf::Sound *m_confirmSound;
	sf::Sound *m_navigateSound;
	sf::Sound *m_backSound;
};

#endif