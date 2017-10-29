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
	ExitMenu();
	void update(XboxController& controller) override;
	void reset() override;

private:
	void yesButtonSelected();
	void noButtonSelected();

	// GUI elements
	Label *m_exitGameLabel;
	Label *m_areYouSureLabel;
	Button *m_yesButton, *m_noButton;
	sf::Texture m_yesTexture, m_noTexture;

	bool m_noButtonPressed;
	bool transitionIn;
	float interpolation;
};

#endif