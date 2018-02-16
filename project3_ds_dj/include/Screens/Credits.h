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
	Credits(sf::View &view, sf::Sound *backSound);
	void update(XboxController& controller, sf::Int32 dt) override;
	void reset() override;

private:
	// GUI elements
	Label *m_creditsLabel;
	Label *m_text[4];
	sf::Texture m_teamPhoto;
	sf::Sound *m_backSound;

	bool m_backButtonPressed;
	bool transitionIn;
	float interpolation;
};

#endif