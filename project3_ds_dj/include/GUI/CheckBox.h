/// <summary>
/// @author Darren Sweeney 
/// </summary>

#ifndef CHECKBOX_H
#define CHECKBOX_H

#include "Widget.h"
#include <functional>

/// <summary>
/// CheckBox Class used for creating Check Boxes onscreen
/// </summary>
class CheckBox : public Widget 
{
public:
	CheckBox();
	CheckBox(sf::Vector2f & positionIn, sf::Color &focusColor, sf::Color &outOfFocus, sf::Color &fillInColor, float boxWidth = 40.0f,
		float boxHeight = 40.0f, sf::Vector2f &startPos = sf::Vector2f(), sf::Vector2f &endPos = sf::Vector2f());
	bool processInput(XboxController & controller);
	virtual void setPosition(sf::Vector2f &position) override;
	void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
	bool getState();
	void setState(bool stateIn);

	// Callback function to link to external functions
	typedef std::function<void()> Callback;
	Callback select;

private:
	bool m_state = false;
	sf::RectangleShape m_checkBoxRect;

	void switchState();

	sf::Color focusColor;
	sf::Color noFocusColor;
	sf::Color fillColor;
};

#endif