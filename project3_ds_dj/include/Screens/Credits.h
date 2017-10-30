/// <summary>
/// @author Darren Sweeney
/// </summary>

#ifndef CREDITS_H
#define CREDITS_H

#include <SFML\Graphics.hpp>
#include "XboxController.h"
#include "GUI\Button.h"
#include "GUI\Label.h"
#include "Screen.h"

class Credits : public Screen
{
public:
	Credits();
	void update(XboxController& controller) override;
	void reset() override;

private:
	// GUI elements
	Label *m_creditsLabel;
	Label *m_names[3];
	sf::Texture m_teamPhoto;

	bool m_backButtonPressed;
	bool transitionIn;
	float interpolation;
};

#endif