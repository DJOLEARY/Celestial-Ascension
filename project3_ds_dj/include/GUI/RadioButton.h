/// <summary>
/// @author Darren Sweeney 
/// </summary>

#ifndef RADIO_BUTTON_H
#define RADIO_BUTTON_H

#include "GUI\Widget.h"

/// <summary>
/// Radio Button class for creating one radio button which will be added to RadioButtons class for managment
/// </summary>
class RadioButton : public Widget
{
public:
	RadioButton(sf::Vector2f & positionIn, sf::Color &focusColor, sf::Color &outOfFocus, sf::Color &fillInColor, float buttonRadius = 20.0f,
		sf::Vector2f &startPos = sf::Vector2f(), sf::Vector2f &endPos = sf::Vector2f());

	virtual void promoteFocus() override;
	virtual void demoteFocus() override;

	void toggle();
	void turnOff();

	void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

private:
	sf::Color focusColor;
	sf::Color noFocusColor;
	sf::Color fillColor;
	float m_radius;
	bool m_isOn;

	sf::CircleShape m_radioButtonCircle;
};

#endif